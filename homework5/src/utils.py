import numpy as np
from typing import List
import cv2
from pathlib import Path
import os
import time
import matplotlib.pyplot as plt

from detectors import Harris, SIFT, BRISK


RAW_DATA_PATH = Path('../data/raw/')


def get_repeatability(desriptions: List[np.ndarray], norm) -> List[int]:
    
    brute_force = cv2.BFMatcher(norm, crossCheck=True)
    
    repeatabilities = []
    for first_idx, first_descriptors in enumerate(desriptions):
        repeats = np.zeros(len(first_descriptors))
        
        for second_idx, second_descriptors in enumerate(desriptions):
            if first_idx == second_idx:
                continue
    
            matched_points = brute_force.match(first_descriptors, second_descriptors)
            for point in matched_points:
                repeats[point.queryIdx] += 1

        repeatabilities.append(np.mean((repeats / len(desriptions))))

    return repeatabilities


def main():
    images = []
    
    for image_name in os.listdir(RAW_DATA_PATH):
        images.append(cv2.imread(str(RAW_DATA_PATH / image_name)))
    
    harris_detector = Harris()
    sift_detector = SIFT()
    brisk_detector = BRISK()
    
    harris_start = time.time()
    harris_keypoints, harris_descriptors = harris_detector.get_descriptors(images)
    harris_end = time.time()
    
    harris_time = (harris_end - harris_start) / len(harris_keypoints) / len(images)
    
    sift_start = time.time()
    sift_keypoints, sift_descriptors = sift_detector.get_descriptors(images)
    sift_end = time.time()
    
    sift_time = (sift_end - sift_start) / len(sift_keypoints) / len(images)
    
    brisk_start = time.time()
    brisk_keypoints, brisk_descriptors = brisk_detector.get_descriptors(images)
    brisk_end = time.time()
    
    brisk_time = (brisk_end - brisk_start) / len(brisk_keypoints) / len(images)
    
    print(f"Harris time for special point: {harris_time} seconds")
    print(f"SIFT time for special point: {sift_time} seconds")
    print(f"BRISK time for special point: {brisk_time} seconds")
    
    figure = plt.figure(figsize=(12, 8))

    plt.plot(get_repeatability(harris_descriptors, cv2.NORM_L2), label='Harris')
    plt.plot(get_repeatability(sift_descriptors, cv2.NORM_L2), label='SIFT')
    plt.plot(get_repeatability(brisk_descriptors, cv2.NORM_HAMMING), label='BRISK')

    plt.title('Repeatability-image dependency', fontsize=20)
    plt.xlabel('Image number', fontsize=18)
    plt.ylabel('Repeatability', fontsize=18)

    plt.grid()
    plt.legend(fontsize=18)

    plt.savefig('results.png')


if __name__ == '__main__':
    main()


