from sklearn.metrics import mean_squared_error
from PIL import Image
import numpy as np
import argparse

def parse_arguments():
    parser = argparse.ArgumentParser(
                        prog = 'compute_psnr',
                        description = 'Compute PSNR for ground truth and result after demosaicing',
                        epilog = 'Wolf is weaker than lion and tiger but he doesn\'t perform in a circus')
    
    parser.add_argument('--ground_truth', dest='ground_truth', type=str, required=True)
    parser.add_argument('--result_image', dest='result_image', type=str, required=True)

    return parser.parse_args()


def main():
    args = parse_arguments()

    result_image = np.array(Image.open(args.result_image))
    ground_truth = np.array(Image.open(args.ground_truth))

    mse = mean_squared_error(result_image.flatten(), ground_truth.flatten())
    psnr = 20 * np.log10(255 / np.sqrt(mse))

    print("PSNR:", psnr)


if __name__ == "__main__":
    main()