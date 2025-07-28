# Introduction

This is an implentation of the paper "AN IMAGE IS WORTH 16X16 WORDS: TRANSFORMERS FOR IMAGE RECOGNITION AT SCALE".

# Why ViT ?

Advantages - 

CNN is robust for extracting the features from the image but fails to extract the global relationship between the pixels at different locations. While transformers can reason out the relationship between patches (it is computationally expensive to use pixels in the linear embeddings). This makes transformers more robust compared to CNN.

Disdvantages - 

The transformers are good extractor of the global relationship but this is at the expense of large data required to train it. It is clear from human's brain that learning spatial or local information is easier than the global information. This is the same case in the transformers.

# Vision transformers (In depth understanding)

## Preprocessing


