import cv2
import numpy as np


def get_sobel_matrix(image: np.ndarray) -> np.ndarray:
    sobel = cv2.Sobel(image, cv2.CV_64F, 1, 1, ksize=9)

    return sobel


def sobel_preprocess(image: np.ndarray, threshold_percent: int = 90) -> np.ndarray:
    sobel = get_sobel_matrix(image)
    result_image = np.copy(sobel)

    threshold = np.percentile(sobel, threshold_percent)
    result_image[result_image <= threshold] = 0
    
    return result_image


def grayscale(image: np.ndarray) -> np.ndarray:
    return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


def main():
    IMAGE_PATH = "./examples/1.jpg"

    image = cv2.imread(IMAGE_PATH)
    grayscale_image = grayscale(image)

    edges_image = sobel_preprocess(grayscale_image)

    cv2.imshow("edges", edges_image)
    cv2.waitKey(0)


if __name__ == "__main__":
    main()