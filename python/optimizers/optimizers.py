class optimizers:
    """! Class to implement different optimizers to minimize the loss and update the parameters"""

    def __init__(self, loss_type):
        """! Constructor to initialize the parameters for optimizers
        @ param loss_type   Type of loss 
        """
        optimizer_type = None
        self.loss_type = loss_type

    def gradient_descent(self, w, b, X, Y, lr):
        """! Gradient descent updates the parameters (weight and bias) by calculating the partial 
        derivative of the loss function
        
        @param  w    Parameter 1 (Weight)
        @param  b    Parameter 2 (Bias)
        @param  X    Input vector
        @param  Y    Actual output
        @param  lr   Learning rate
        @returns    Updated parameter 1
        @returns    Updated parameter 2
        """
        dw = 0
        db = 0
        N = len(X)
        
        # Partial derivative of the cost function (y_actual - y_pred)^2 i.e mean square error
        # dJ(w)/dw = -2x(y - (mx + b))
        # dJ(b)/db = -2(y - (mx + b)) 
        # TODO Implement for different cost function (ex. cross entropy loss and other popular loss fn)
        # TODO Implement GD with momentum
        
        for i in range(N):
            dw += -2 * X[i] * (Y[i] - (w * X[i] + b))
            db += -2 * (Y[i] - (w * X[i] + b))

        # Update the parameters p_new = p_old - (lr * partial_derivative(J(p))
        w -= (dw / N) * lr
        b -= (db / N) * lr

        return w, b
    
    def stochastic_gradient_descent(self, w, b, X, Y, lr):
        """! Not implemented as it is similar to gradient descent but with a batch of input data"""
        raise NotImplementedError(self.__class__.__name__ + '.stochastic_gradient_descent()')