import json


imagesLibPath = "./images"

import torch
import numpy as np
import monai.transforms as transforms
from PIL import Image
import os
import datetime
#torch==2.3.0
#numpy=1.26.4
#monai=1.3.2
class MyUNetModel:
    def __init__(self, model_path):
        self.device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
        self.model = torch.load(model_path, map_location=self.device)

    def blend_images(self, image, mask, alpha=0.5):
        image = (image - image.min()) / (image.max() - image.min())
        mask = mask.astype(np.uint8)
        colored_mask = np.zeros((*mask.shape, 3), dtype=np.uint8)
        colored_mask[mask == 1] = [255, 0, 0]
        blended_image = (1 - alpha) * image + alpha * colored_mask / 255
        return blended_image

    def predict(self, image_path, save_dir):
        if not os.path.exists(save_dir):
            os.makedirs(save_dir)

        image = Image.open(image_path)
        width, height = image.size

        transforms_inference = transforms.Compose(
            [
                transforms.LoadImage(image_only=True),
                transforms.EnsureChannelFirst(),
                transforms.ScaleIntensityRange(
                    a_min=0,
                    a_max=255,
                    b_min=0.0,
                    b_max=1.0,
                    clip=True,
                ),
                transforms.CenterScaleCrop(roi_scale=0.8),
                transforms.ResizeWithPadOrCrop(spatial_size=(width, width))
            ]
        )

        image = transforms_inference(image_path)
        image_tensor = torch.unsqueeze(image, 0).to(self.device)
        with torch.no_grad():
            output = self.model(image_tensor)
            # Картинка
            image = image.permute(1, 2, 0).cpu().numpy()
            # Результат
            predicted_mask = output.argmax(dim=1).cpu().numpy()
            blended_image = self.blend_images(image,predicted_mask, 0.4)
            timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
            # Ориг картинка 
            origin_path = f"{save_dir}/original_{timestamp}.jpg"
            original_image = Image.fromarray((image * 255).astype(np.uint8))
            original_image.save(origin_path)
            # Маска
            blended_path = f"{save_dir}/result_{timestamp}.jpg"
            blended_image_pil = Image.fromarray((blended_image[0] * 255).astype(np.uint8))
            blended_image_pil.save(blended_path)
        return origin_path, blended_path
    
if __name__ == '__main__':
    jsonPath = 'data.json'
    with open(jsonPath, 'r') as file:
        data = json.load(file)
        imageToPredict = data['imageToPredict']
    unplus = MyUNetModel("hema_unet.pth")
    origPath, finalPath = unplus.predict(imageToPredict, "images")

    data = {
        'orig': origPath,
        'final': finalPath
    }

    with open(jsonPath, 'w') as f:
        json.dump(data, f)