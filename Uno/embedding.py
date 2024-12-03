from PIL import Image
from glob import glob
import os


output = ""
mapping = ""
for image_path in glob("cards" + os.sep + "*.png"):
    img = Image.open(image_path).convert("RGBA")
    print(image_path, img.getdata()[0])
    hexdata = list(map(lambda i: ",".join(map(hex, i)), img.getdata()))

    varname = "CARD_TEXTURE_" + image_path.split(os.sep)[1].split(".")[0].upper()
    output += "sf::Uint8* " + varname + " = {" + ",".join(hexdata) + "}\n"
    mapping += f'if (filename == \"{image_path}\") {{ return {varname}; }}\n'
print(output)
print(mapping)
