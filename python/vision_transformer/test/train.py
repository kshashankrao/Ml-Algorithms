import torch
import torchvision
from torchvision import transforms
import torchvision.datasets as datasets

import sys
sys.path.append("../src/")
sys.path.append("../../utils/")
import image_utils
from vision_transformer import ViT

import params

batch_size = 8
workers = 1
show_image = False

def main():
    
    # Load the dataset
    transform = transforms.Compose([transforms.ToTensor()])
    mnist_trainset = datasets.MNIST(root='../data', train=True, download=True, transform=transform)
    mnis t_testset = datasets.MNIST(root='../data', train=False, download=True, transform=transform)
    trainloader = torch.utils.data.DataLoader(mnist_trainset, batch_size=batch_size, shuffle=True, num_workers=workers)
    testloader = torch.utils.data.DataLoader(mnist_testset, batch_size=batch_size, shuffle=False, num_workers=workers)
    
    #model = ViT()
    if show_image:
        image_iter = next(trainloader)
        image_utils.mplt_imshow(next(torchvision.utils.make_grid(inputs)))

    for i, data in enumerate(trainloader):
        inputs, labels = data
    
if __name__ == '__main__':
    main()




