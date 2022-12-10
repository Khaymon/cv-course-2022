import cv2
import numpy as np

from utils.utils_functions import get_upper_power, pad_image, shift


class FHT:
    def transform(self, image: np.ndarray) -> np.ndarray:
        desired_height = get_upper_power(image.shape[0], 2)
        desired_width = get_upper_power(image.shape[1], 2)

        preprocessed_image = pad_image(image, desired_height, desired_width)

        result_right = self._fht(preprocessed_image, direction=1)
        result_right = result_right[:image.shape[0], :image.shape[1]]

        result_left = self._fht(preprocessed_image, direction=-1)
        result_left = result_left[:image.shape[0], :image.shape[1]]

        result = np.concatenate((result_left[:, ::-1], result_right), axis=1)

        return result


    def _fht(self, image: np.ndarray, direction: int) -> np.ndarray:
        if image.shape[1] == 1:
            return image

        left_result = self._fht(image[:, :image.shape[1] // 2], direction)
        right_result = self._fht(image[:, image.shape[1] // 2:], direction)

        return self._merge(left_result, right_result, direction)

    
    def _merge(self, left_result: np.ndarray, right_result: np.ndarray, direction: int) -> np.ndarray:
        result = np.zeros(shape=(left_result.shape[0], left_result.shape[1] * 2))

        for column_idx in range(result.shape[1]):
            right_result_shifted = shift(right_result[:, column_idx // 2], direction * int(np.ceil(column_idx / 2)))
            result[:, column_idx] = left_result[:, column_idx // 2] + right_result_shifted

        return result / result.max(initial=2)
