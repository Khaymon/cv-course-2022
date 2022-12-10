# Fast Hough Transform

## Pipeline
1. Extracting the edges of image by Sobel filter with $9\times 9$ kernel size and $0.9$-percentile threshold for values.

## Results
| <img src="./examples/1.jpg" alt="drawing" width="500"/>       | <img src="./transformed/1_bilinear.jpg" alt="drawing" width="500"/>           |
|:-------------------------------------------------------------:| :--------------------------------------------------------------------:        |
|                                *Original image*               |                  *Bilinear approximation result*                              |
|                                                               |                                                                               |

| <img src="./examples/2.jpg" alt="drawing" width="500"/> | <img src="./transformed/2_bilinear.jpg" alt="drawing" width="500"/>                     |
|:-----------------------------------------------------------------------:| :---------------------------------------------------------------------: |
|                            *Original image*                             |         *Bilinear approximation result*                                 |
|                                                                         |                                                                         |

| <img src="./examples/3.jpg" alt="drawing" width="500"/>       | <img src="./transformed/3_nearest.jpg" alt="drawing" width="500"/>            |
|:-------------------------------------------------------------:| :--------------------------------------------------------------------:        |
|                                *Original image*               |                  *Nearest neighbour approximation result*                     |
|                                                               |                                                                               |

| <img src="./examples/4.jpg" alt="drawing" width="500"/> | <img src="./transformed/4_nearest.jpg" alt="drawing" width="500"/>                       |
|:-----------------------------------------------------------------------:| :---------------------------------------------------------------------: |
|                            *Original image*                             |         *Nearest neighbour approximation result*                        |
|                                                                         |                                                                         |
