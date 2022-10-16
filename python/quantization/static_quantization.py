
'''
Quantization - Convert the float32 dtype to int8. Therefore reducing the computational time.
Here static quantization is performed. The model is trained in normal way. It is then quantized and saved using jit.

Observation -
Both model size and runtime is reduced. 0.8s vs 0.4s
'''
from __future__ import print_function

import argparse
import time
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
from torch.optim.lr_scheduler import StepLR

from google.colab import drive
drive.mount('/gdrive', force_remount=True)



class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 32, 3, 1)
        self.conv2 = nn.Conv2d(32, 64, 3, 1)
        self.dropout1 = nn.Dropout(0.25)
        self.dropout2 = nn.Dropout(0.5)
        self.fc1 = nn.Linear(9216, 128)
        self.fc2 = nn.Linear(128, 10)
        self.quant = torch.quantization.QuantStub()
        self.dequant = torch.quantization.DeQuantStub()
        self.relu1 = nn.ReLU()
        self.relu2 = nn.ReLU()


    def forward(self, x):
        x = self.quant(x)
        x = self.conv1(x)

        # NOTE: Functional relu (F.relu) not working for quatization ? Fix - It is called as nn.relu
        x = self.relu1(x)
        x = self.conv2(x)
        x = self.relu2(x)
        x = F.max_pool2d(x, 2)
        x = self.dropout1(x)
        x = torch.flatten(x, 1)
        x = self.fc1(x)
        x = F.relu(x)
        x = self.dropout2(x)
        x = self.fc2(x)

        # NOTE: Softmax layer removed from here as quantization was not supporting. It is called outside this class.
        output = self.dequant(x)

        return output


def train(args, model, device, train_loader, optimizer, epoch):
    model.train()
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        output = model(data)
        loss = F.nll_loss(output, target)
        loss.backward()
        optimizer.step()
        if batch_idx % args.log_interval == 0:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                100. * batch_idx / len(train_loader), loss.item()))
            if args.dry_run:
                break


def test(model, device, test_loader):
    model.eval()
    test_loss = 0
    correct = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item()  # sum up batch loss
            pred = output.argmax(dim=1, keepdim=True)  # get the index of the max log-probability
            correct += pred.eq(target.view_as(pred)).sum().item()

    test_loss /= len(test_loader.dataset)

    print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))


def main():
    # Training settings
    parser = argparse.ArgumentParser(description='PyTorch MNIST Example')
    parser.add_argument('--batch-size', type=int, default=64, metavar='N',
                        help='input batch size for training (default: 64)')
    parser.add_argument('--test-batch-size', type=int, default=1000, metavar='N',
                        help='input batch size for testing (default: 1000)')
    parser.add_argument('--epochs', type=int, default=1, metavar='N',
                        help='number of epochs to train (default: 14)')
    parser.add_argument('--lr', type=float, default=1.0, metavar='LR',
                        help='learning rate (default: 1.0)')
    parser.add_argument('--gamma', type=float, default=0.7, metavar='M',
                        help='Learning rate step gamma (default: 0.7)')
    parser.add_argument('--no-cuda', action='store_true', default=True,
                        help='disables CUDA training')
    parser.add_argument('--no-mps', action='store_true', default=False,
                        help='disables macOS GPU training')
    parser.add_argument('--dry-run', action='store_true', default=False,
                        help='quickly check a single pass')
    parser.add_argument('--seed', type=int, default=1, metavar='S',
                        help='random seed (default: 1)')
    parser.add_argument('--log-interval', type=int, default=10, metavar='N',
                        help='how many batches to wait before logging training status')
    parser.add_argument('--save-model', action='store_true', default=True,
                        help='For Saving the current Model')
    args, unknown = parser.parse_known_args()

    use_cuda = not args.no_cuda and torch.cuda.is_available()
    use_mps = not args.no_mps and torch.backends.mps.is_available()

    is_predict = True
    is_train = False


    torch.manual_seed(args.seed)

    if use_cuda:
        device = torch.device("cuda")
    elif use_mps:
        device = torch.device("mps")
    else:
        device = torch.device("cpu")

    train_kwargs = {'batch_size': args.batch_size}
    test_kwargs = {'batch_size': args.test_batch_size}
    if use_cuda:
        cuda_kwargs = {'num_workers': 1,
                       'pin_memory': True,
                       'shuffle': True}
        train_kwargs.update(cuda_kwargs)
        test_kwargs.update(cuda_kwargs)

    transform=transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
        ])

    dataset1 = datasets.MNIST('/gdrive/My Drive/Colab Notebooks/dataset', train=True, download=False,
                       transform=transform)
    dataset2 = datasets.MNIST('/gdrive/My Drive/Colab Notebooks/dataset', train=False,
                       transform=transform)
    train_loader = torch.utils.data.DataLoader(dataset1,**train_kwargs)
    test_loader = torch.utils.data.DataLoader(dataset2, **test_kwargs)
    device = "cpu"
    model = Net().to(device)
    
    if is_predict:
      model.load_state_dict(torch.load("/gdrive/My Drive/Colab Notebooks/mnist_cnn.pt"))
      model.to("cpu")
      model.eval()
      
      ########## Compute the time taken without quantization ##########
      test_loss = 0
      correct = 0
      with torch.no_grad():
        for data, target in test_loader:
          t1 = time.time()
          output = model(data)
          output = F.log_softmax(output, dim=1)
          print("Time taken ",time.time() - t1)
          test_loss += F.nll_loss(output, target, reduction='sum').item()  # sum up batch loss
          pred = output.argmax(dim=1, keepdim=True)  # get the index of the max log-probability
          correct += pred.eq(target.view_as(pred)).sum().item()

      test_loss /= len(test_loader.dataset)

      print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))

      backend = "fbgemm"  # x86 machine

      torch.backends.quantized.engine = backend
      model.qconfig = torch.ao.quantization.default_qconfig
      
      model = torch.quantization.fuse_modules(model, [['conv1', 'relu1']])
      model = torch.quantization.fuse_modules(model, [['conv2', 'relu2']])
      
      qmodel = torch.ao.quantization.prepare(model, inplace=True)
      
      qmodel.eval()
      qmodel.to(device)

      # This prediction is required for the model to warm up.
      with torch.no_grad():
        for data, target in test_loader:
          output = model(data)
          output = F.log_softmax(output, dim=1)
      qmodel = torch.ao.quantization.convert(model)
      qmodel.eval()
      qmodel.to(device)
    
      ########## Compute the time taken with quantization ##########
      test_loss = 0
      correct = 0
      with torch.no_grad():
        for data, target in test_loader:
          t1 = time.time()
          output = qmodel(data)
          output = F.log_softmax(output, dim=1)
          print("Quantized Time taken ",time.time() - t1)
          test_loss += F.nll_loss(output, target, reduction='sum').item()  # sum up batch loss
          pred = output.argmax(dim=1, keepdim=True)  # get the index of the max log-probability
          correct += pred.eq(target.view_as(pred)).sum().item()

        torch.jit.save(torch.jit.script(qmodel), "/gdrive/My Drive/Colab Notebooks/quantized_mnist_cnn.pt")

      test_loss /= len(test_loader.dataset)

      print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))
          
    if is_train:
      optimizer = optim.Adadelta(model.parameters(), lr=args.lr)

      scheduler = StepLR(optimizer, step_size=1, gamma=args.gamma)
      for epoch in range(1, args.epochs + 1):
          train(args, model, device, train_loader, optimizer, epoch)
          test(model, device, test_loader)
          scheduler.step()

      if args.save_model:
          torch.save(model.state_dict(), "/gdrive/My Drive/Colab Notebooks/mnist_cnn.pt")


if __name__ == '__main__':       
    main()
