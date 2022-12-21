# Demosaicing with Variable Number of Gradients (VNG)
## Task description
Having an input image as an Bayer filter the goal is to retrieve natural image colors.  
## Results
<div align="center">

| <img src="./resources/RGB_CFA.bmp" alt="drawing" width="500"/>   |
|:----------------------------------------------------------------:|
|                                *Input image*                     |
|                                                                  |  

</div>  


| <img src="./resources/Original.bmp" alt="drawing" width="500"/>         | <img src="./resources/RGB_CFA_result.bmp" alt="drawing" width="500"/>   |
|:-----------------------------------------------------------------------:| :---------------------------------------------------------------------: |
|                            *Ground truth image*                         |         *VNG result*                                                    |
|                                                                         |                                                                         |
 
PSNR metric for test image is $33.04$. Speed is $11.08$ seconds per megapixel.
