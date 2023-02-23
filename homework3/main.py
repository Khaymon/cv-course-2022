import cv2
import numpy as np
import os
import matplotlib.pyplot as plt
import seaborn as sns
from time import time
from typing import List

from fast_hough_transform import FHT
from utils.preprocessing import grayscale, sobel_preprocess
from utils.utils_functions import get_angle, rotate_image


INTERPOLATION_METHODS = {
    "nearest": cv2.INTER_NEAREST, 
    "bilinear": cv2.INTER_LINEAR
}

EXAMPLES_DIR_PATH = "./examples/"
TRANSFORMED_DIR_PATH = "./transformed/"


def transform_image(image_num: int, interpolation_method: str, repeats: int = 3):
    image_path = os.path.join(EXAMPLES_DIR_PATH, str(image_num) + ".jpg")
    transformed_image_path = os.path.join(TRANSFORMED_DIR_PATH, str(image_num) + f"_{interpolation_method}.jpg")

    image = cv2.imread(image_path)
    grayscale_image = grayscale(image)
    image_preprocessed = sobel_preprocess(grayscale_image)
    cv2.imwrite("sobel_filtering.jpg", image_preprocessed)

    fht = FHT()


    final_time = 0
    for _ in range(repeats):
        start = time()
        fht_transformed = fht.transform(image_preprocessed)
        end = time()

        final_time += end - start
    final_time /= repeats

    angle = get_angle(fht_transformed, INTERPOLATION_METHODS[interpolation_method])
    rotated_image = rotate_image(image, -angle)

    cv2.imwrite(transformed_image_path, rotated_image)

    return image.shape[0] * image.shape[1], final_time


def make_plot(pixels: List[int], seconds: List[float]) -> None:
    sns.set_style("whitegrid")
    fig = plt.figure(figsize=(12, 8))
    plt.scatter(pixels, seconds)
    plt.title("Time dependency from number of megapixels", fontsize=18)
    plt.xlabel("Megapixels", fontsize=16)
    plt.ylabel("Time (seconds)", fontsize=16)

    plt.show()


def main():
    results = []
    for i in range(1, 11):
        pixels, seconds = transform_image(i, "bilinear")
        pixels /= 1_000_000

        results.append((pixels, seconds))

    results = sorted(results, key=lambda x: x[0])
    pixels_list = list(map(lambda x: x[0], results))
    seconds_list = list(map(lambda x: x[1], results))

    make_plot(pixels_list, seconds_list)


if __name__ == "__main__":
    main()
