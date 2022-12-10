import numpy as np
import math
import cv2


def pad_image(image: np.ndarray, height: int, width: int) -> np.ndarray:
    assert image.shape[0] <= height and image.shape[1] <= width, "Image sizes should be not greater than desired"

    additional_height = height - image.shape[0]
    additional_width = width - image.shape[1]

    result_image = np.pad(image, [(0, additional_height), (0, additional_width)])

    return result_image


def get_upper_power(number: int, base: int) -> int:
    power = int(np.ceil(math.log(number, base)))
    
    return base ** power


def get_angle(fht_result: np.ndarray, interpolation_method) -> int:
    resized = cv2.resize(fht_result, (90, fht_result.shape[0]), interpolation=interpolation_method)
    angle = np.where(resized == resized.max())[1][0] - 45

    return angle


def rotate_image(image: np.ndarray, angle: int) -> np.ndarray:
    center = (image.shape[1] / 2, image.shape[0] / 2)
    matrix = cv2.getRotationMatrix2D(center, angle, 1)
    rotated_image = cv2.warpAffine(image, matrix, (image.shape[1], image.shape[0]))
    
    return rotated_image


def shift(array: np.ndarray, shift_size: np.ndarray) -> np.ndarray:
    result_array = np.zeros_like(array)
    if shift_size > 0:
        result_array[shift_size:] = array[:-shift_size]
    elif shift_size < 0:
        result_array[:shift_size] = array[-shift_size:]
    else:
        result_array = array

    return result_array
