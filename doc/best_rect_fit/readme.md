# Tried and failed algorithms

## Using PCA (Code missing)

### Idea
1. The idea is to find the direction in which the blob points to, using the covariance matrix. 
2. The largest eigen vector corresponds to the major axis.
3. Get the rotation angle (between the largest eigen vector and x axis). Find the rectangle along this angle using simple rect fiitting.

### Conclusion
The final results was not as expected. The PCA was failing to find the correct direction when the blob is irregular.

# Algorithm

In Progress.....

