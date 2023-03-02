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
    
    parser.add_argument("-t", "--textures", type=str,
                        help="Path to the textures directory",
                        dest="textures_path",
                        default="../data/textures/")
    
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


def create_image(paper_image: np.ndarray, 
                 background_image: np.ndarray, 
                 texture_image: np.ndarray,
                 background_slot: np.ndarray) -> np.ndarray:
    
    paper_image = augment_paper(paper_image, texture_image)
    result_image = place_image(paper_image, background_image, background_slot)
    result_image = augment_final_image(result_image)
    
    return result_image


def create_data(papers_path: str,
                backgrounds_path: str,
                textures_path: str,
                results_path: str,
                markup: Dict[str, List[List[int]]]) -> None:

    papers = os.listdir(papers_path)
    backgrounds = os.listdir(backgrounds_path)
    textures = os.listdir(textures_path)

    for paper_name in tqdm(papers):
        for texture_name in tqdm(textures):
            for background_name in backgrounds:
                paper_image = cv2.imread(os.path.join(papers_path, paper_name))
                background_image = cv2.imread(os.path.join(backgrounds_path, background_name))
                texture_image = cv2.imread(os.path.join(textures_path, texture_name))
                
                result_image = create_image(paper_image, background_image,
                                            texture_image, np.float32(markup[background_name]))
                
                result_image_path = os.path.join(results_path, f"{paper_name}_{background_name}_{texture_name}.png")
                cv2.imwrite(result_image_path, result_image)


def main():
    args = parse_arguments()
    with open(args.markup_path, 'r') as input_file:
        backgrounds_markup = json.load(input_file)
    
    create_data(papers_path=args.papers_path, 
                backgrounds_path=args.backgrounds_path,
                textures_path=args.textures_path, 
                results_path=args.results_path, 
                markup=backgrounds_markup)


if __name__ == "__main__":
    main()