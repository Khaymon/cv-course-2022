import argparse
import cv2
import numpy as np
from typing import List, Dict
import os
from tqdm import tqdm
import json

from augment import *


def parse_arguments():
    parser = argparse.ArgumentParser(
        prog="Images Augmentation",
        description="Augmentation of paper images"
    )
    
    parser.add_argument("-p", "--papers", type=str, 
                        help="Path to the papers directory", 
                        dest="papers_path",
                        default="../data/images/")
    
    parser.add_argument("-b", "--backgrounds", type=str,
                        help="Path to the background images directory",
                        dest="backgrounds_path",
                        default="../data/backgrounds/")
    
    parser.add_argument("-r", "--results", type=str,
                        help="Path to the augmented images directory",
                        dest="results_path",
                        default="../data/augmented/")
    
    parser.add_argument("-m", "--markup", type=str,
                        help="Path to the markup of backgrounds",
                        dest="markup_path",
                        default="../data/background_markup.json")
    
    args = parser.parse_args()
    return args


def overlap_images(background_image: np.ndarray, front_image: np.ndarray):
    result_background = background_image.copy()
    
    for i in range(front_image.shape[0]):
        for j in range(front_image.shape[1]):
            for channel in range(3):
                if front_image[i, j, 3] != 0:
                    result_background[i, j, channel] = front_image[i, j, channel]
    
    return result_background


def create_data(papers_path: str,
                backgrounds_path: str,
                results_path: str,
                markup: Dict[str, List[List[int]]]):

    papers = os.listdir(papers_path)
    backgrounds = os.listdir(backgrounds_path)

    for paper_name in tqdm(papers):
        for background_name in backgrounds:
            paper_image = cv2.imread(os.path.join(papers_path, paper_name))
            paper_image = augment_paper(paper_image)
            
            background_image = cv2.imread(os.path.join(backgrounds_path, background_name))

            paper_image = cv2.cvtColor(paper_image, cv2.COLOR_RGB2RGBA)
            background_image = cv2.cvtColor(background_image, cv2.COLOR_RGB2RGBA)

            background_rows = background_image.shape[0]
            background_columns = background_image.shape[1]

            paper_rows = paper_image.shape[0]
            paper_columns = paper_image.shape[1]    

            paper_position = np.float32([[0, 0], 
                                         [0, paper_rows - 1], 
                                         [paper_columns - 1, paper_rows - 1], 
                                         [paper_columns - 1, 0]]
                                        )
            
            slot_position = np.float32(markup[background_name])

            transform = cv2.getPerspectiveTransform(slot_position, paper_position)
            inverse_transform = np.linalg.pinv(transform)

            paper_image_transformed = cv2.warpPerspective(paper_image, inverse_transform, 
                                                          (background_columns, background_rows), 
                                                          cv2.INTER_LINEAR_EXACT)
            
            result_image = overlap_images(background_image, paper_image_transformed)
            result_image = augment_final_image(result_image)
            
            result_image_path = os.path.join(results_path, f"{paper_name}_{background_name}.png")
            cv2.imwrite(result_image_path, result_image)


def main():
    args = parse_arguments()
    with open(args.markup_path, 'r') as input_file:
        backgrounds_markup = json.load(input_file)
    
    create_data(papers_path=args.papers_path, backgrounds_path=args.backgrounds_path,
                results_path=args.results_path, markup=backgrounds_markup)


if __name__ == "__main__":
    main()