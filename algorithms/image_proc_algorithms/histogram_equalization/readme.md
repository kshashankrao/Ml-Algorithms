# Understanding Cumulative distribution function

According to wikipedia, it is defined as:

When a random variable X is evaluated at x (current time interval), CDF is the probability of X being less than or equal to x.
It is the PDF from -infinity to x.


# Algorithm

1. Get the histogram of the pixel intensity
2. Normalize the histogram p<sub>i</sub> / N, where p<sub>i</sub> is the intensity of i<sup>th</sup> pixel and N is the total number of pixels
3. I<sub> Hist_Equalized(i,j)</sub> = floor (L - 1) Σp<sub>n</sub>

# Reference

1. https://www.math.uci.edu/icamp/courses/math77c/demos/hist_eq.pdf