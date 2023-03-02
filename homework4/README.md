## Images augmentations

Objective of this task is to provide augmentations for the set of perfectly rendered papers. Papers have to be put on some surfaces with further addition of camera and printing defects.

## Methodolohy
I split pipeline of augmentation into three four parts: texture addition, printing defects, paper placing, camera defects.

### Texture addition
Here, having an image of paper and an image of paper texture, I blend them together.

| <img src="./examples/paper_example.png" alt="drawing" width="500"/> | <img src="./examples/texture_example.png" alt="drawing" width="500"/> | <img src="./examples/texture_result.png" alt="drawing" width="500"/> |
| :-----------------------------------------------------------------: | :-------------------------------------------------------------------: | :------------------------------------------------------------------: |
|                            *Paper image*                            |                            *Texture image*                            |                           *Blending image*                           |
|                                                                     |                                                                       |                                                                      |

### Printing defects
I add some vertical lines to imitate printing defects.

<div align="center">

| <img src="./examples/printing_defects_example.png" alt="drawing" width="500"/> |
| :----------------------------------------------------------------------------: |
|                         *Example of printing defects*                          |
|                                                                                |

</div>

### Paper placing
Now, it's time to place our paper image into background's surface. Here I use perspective transformation to get paper image coordinates in background image and blend transformed paper image and a background

| <img src="./examples/paper_example.png" alt="drawing" width="500"/> | <img src="./examples/art_and_museum_example.jpg" alt="drawing" width="500"/> | <img src="./examples/result_placing.png" alt="drawing" width="500"/> |
| :-----------------------------------------------------------------: | :--------------------------------------------------------------------------: | :------------------------------------------------------------------: |
|                            *Paper image*                            |                              *Background image*                              |                            *Result image*                            |
|                                                                     |                                                                              |                                                                      |

### Camera defects
Here I add Vignette filter and movement blur.

<div align="center">

| <img src="./examples/final_result_example.png" alt="drawing" width="500"/> |
| :----------------------------------------------------------------------------: |
|                         *Final result*                          |
|                                                                                |

</div>