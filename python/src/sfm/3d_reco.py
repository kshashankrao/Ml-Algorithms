import numpy as np

def eight_point_alogirthm(pts1, pts2, M):

    '''
    Algorithm:

    1.  Normalize the matched points pts/max(img_height, img_width)
    
    2.  Ax = 0
    
        Given - A
        To find - x
        
        where,
        A is matrix consisting of combination of the points
        x consists of elements of fundamental matrix

        x is solved using SVD = F_
    
    3. Contraint the F_ to rank 2
    4. Unnormalize the Fundamental matrix
    '''

    # Create a trasnformation matrix
    T = np.eye(3,3)
    T = T / M
    T[2][2] = 1
    
    # Normalize the points
    pts1 = pts1 / M
    pts2 = pts2 / M

    n = len(pts1)
    A = np.zeros((n,9))

    for i in range(n):
        A[i][0] = pts1[i][0] * pts2[i][0]
        A[i][1] = pts1[i][0] * pts2[i][1]
        A[i][2] = pts1[i][0]
        A[i][3] = pts1[i][1] * pts2[i][0]
        A[i][4] = pts1[i][1] * pts2[i][1]
        A[i][5] = pts1[i][1] 
        A[i][6] = pts2[i][0] 
        A[i][7] = pts2[i][1] 
        A[i][8] = 1


    _, _, v_ = np.linalg.svd(A)

    # F_ corresponds to the least singular value
    f_ = v_[-1].reshape(3,3)
    
    # Apply rank 2 constraint
    # https://en.wikipedia.org/wiki/Eight-point_algorithm
    u, s, v = np.linalg.svd(f_)
    s[2] = 0
    f = np.dot(u, np.dot(np.diag(s),v))

    # Unnormalize the matrix
    f = np.dot(np.transpose(T), np.dot(f, T))

    return f