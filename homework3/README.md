# Fast Hough Transform

## Pipeline
Firstly, we extract the edges of image by Sobel filter with $9\times 9$ kernel size and $0.9$-percentile threshold for values.  
| <img src="./examples/10.jpg" alt="drawing" width="500"/>       | <img src="./transformed/sobel_filtering.jpg" alt="drawing" width="500"/>     |
|:-------------------------------------------------------------:| :--------------------------------------------------------------------:        |
|                                *Original image*               |                  *Sobel filtering intermediate result*                        |
  
  
Secondly, we use Fast Hough Transform to get a heatmap in parameters space and find an angle with largest value. After that we need to normalize this angle
by $45$ degrees and rotate the image using one of the interpolation algorithms (bilinear or nearest neighbor).

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
