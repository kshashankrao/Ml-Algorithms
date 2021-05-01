class optimizers:
    def __init__():
        """! Constructor to initialize the parameters for optimizers"""
        optimizer_type = None

    def gradient_descent(self, w, b, X, Y, lr):
        """! Gradient descent updates the parameters (weight and bias) by calculating the partial 
        derivative of the loss function
        
        @param Parameter 1 (Weight)
        @param Parameter 2 (Bias)
        @param Input vector
        @param Actual output
        @param Learning rate
        @returns Updated parameter 1
        @returns Updated parameter 2
        """
        w_ = 0
        b_ = 0
        N = len(X)
        
        # Partial derivative of the cost function (y_actual - y_pred)^2 i.e mean square error
        # dJ(w)/dw = -2x(y - (mx + b))
        # dJ(b)/db = -2(y - (mx + b)) 
        # TODO Implement for different cost function (ex. cross entropy loss and other popular loss fn)
        
        for i in range(N):
            w_ += -2 * X[i] * (Y[i] - (w * X[i] + b))
            b_ += -2 * (Y[i] - (w * X[i] + b))

        w -= (m_deriv / N) * lr
        b -= (b_deriv / N) * lr

        return w, b
            
