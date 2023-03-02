import numpy as np
import cv2
from typing import Tuple
import imgaug.augmenters as iaa


def add_vertical_lines(image: np.ndarray, 
                       proba: float = 0.001, 
                       min_width: int = 1, 
                       max_width: int = 3) -> np.ndarray:
    result_image = image.copy()
    mask = np.random.binomial(1, proba, size=image.shape[1])
    
    start_indices = np.where(mask)[0]
    for start_index in start_indices:
        width = np.random.randint(min_width, max_width + 1)
        end_index = start_index + width
        
        result_image[:, start_index:end_index] = 0
        
    return result_image


def add_noise(image: np.ndarray, scale_factor: float = 0.1) -> np.ndarray:
    result_image = image.copy()
    gaussian_noise = iaa.AdditiveGaussianNoise(scale=scale_factor*255)
    
    result_image = gaussian_noise(image=result_image)
    return result_image


def add_gaussian_blur(image: np.ndarray, 
                      sigma: Tuple[float, float] = (0.0, 0.3)) -> np.ndarray:
    result_image = image.copy()
    gaussian_blur = iaa.GaussianBlur(sigma=sigma)
    
    result_image = gaussian_blur(image=result_image)
    return result_image


def add_motion_blur(image: np.ndarray, k: int = 8) -> np.ndarray:
    result_image = image.copy()
    motion_blur = iaa.MotionBlur(k=k)
    
    result_image = motion_blur(image=result_image)
    return result_image
    

def add_vignette(image: np.ndarray, 
                 first_std: float = 0.6,
                 second_std: float = 0.6,
                 ) -> np.ndarray:
    result_image = image.copy()
    
    height, width = image.shape[:2]

    # create gaussian kernel on each axis
    kernelH = cv2.getGaussianKernel(width, first_std * height).reshape([1, -1])
    kernelV = cv2.getGaussianKernel(height, second_std * width).reshape([-1, 1])

    kernel = kernelH * kernelV # reshape to [h, w]
    kernel = kernel / kernel.max() # normalize

    # reshape to [h, w, 1]
    kernel = np.expand_dims(kernel, axis=2) 
    # Elementwise multiplication of 
    # [h, w, 3] and [h, w, 1]
    result_image = np.multiply(result_image, kernel)
    
    return result_image


def add_paper_texture(image: np.ndarray,
                      texture: np.ndarray,
                      alpha: float = 0.5,
                      gamma: float = 3.0):
    result_image = cv2.resize(texture, image.shape[:2]).transpose((1, 0, 2))
    result_image = result_image = cv2.addWeighted(result_image, alpha, image,
                                                  1 - alpha, 0.0, gamma)
    
    return result_image


def augment_paper(image: np.ndarray, texture: np.ndarray) -> np.ndarray:
    result_image = image.copy()
    result_image = add_paper_texture(image, texture)
    result_image = add_vertical_lines(image)
    gaussian_noise = iaa.AdditiveGaussianNoise(scale=0.2*255)
    result_image = gaussian_noise(image=result_image)
    
    return result_image


def augment_final_image(image: np.ndarray) -> np.ndarray:
    result_image = image.copy()
    
    result_image = add_motion_blur(result_image)
    result_image = add_vignette(result_image)
    
    return result_image