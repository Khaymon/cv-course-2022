import cv2
import numpy as np

from typing import Union, List, Tuple


class Detector:
    def __init__(self):
        raise NotImplementedError
    

    def get_descriptors(self, images: Union[np.ndarray, List[np.ndarray]]):
        if isinstance(images, list):
            keypoints = []
            descriptions = []
            
            for image in images:
                image_keypoints, image_descriptions = self._get_image_descriptors(image)
                
                keypoints.append(image_keypoints)
                descriptions.append(image_descriptions)
                
            return keypoints, descriptions
        else:
            print("HERE")
            return self._get_image_descriptors(images)

    
    def _get_image_descriptors(self, images: np.ndarray):
        raise NotImplementedError
    
    
class Harris(Detector):
    def __init__(self):
        pass
    
    
    def _get_image_descriptors(self, image: np.ndarray):
        harris_desription = cv2.dilate(cv2.cornerHarris(np.float32(cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)), 2, 3, 0.01), None)
        harris_keypoints = (harris_desription > 0.01 * harris_desription.max()).nonzero()
        
        return harris_keypoints[0], np.transpose(harris_desription[harris_keypoints])
    
    
class SIFT(Detector):
    def __init__(self):
        self.sift = cv2.SIFT_create()
        
    
    def _get_image_descriptors(self, image: np.ndarray):
        sift_keypoints, sift_description = self.sift.detectAndCompute(image, None)
        
        return sift_keypoints, sift_description
    

class BRISK(Detector):
    def __init__(self):
        self.brisk = cv2.BRISK_create()


    def _get_image_descriptors(self, image: np.ndarray):
        brisk_keypoints, brisk_description = self.brisk.detectAndCompute(image, None)
        
        return brisk_keypoints, brisk_description