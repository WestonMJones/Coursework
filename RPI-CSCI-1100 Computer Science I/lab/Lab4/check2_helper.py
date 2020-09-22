from PIL import Image

def make_square(im):
    x = im.size[0]
    y = im.size[1]
    sd = min(im.size[0],im.size[1])
    
    new_im = Image.new("RGB", (sd,sd), "white")
    new_im = im.crop((0,0,sd,sd))
    
    
    return new_im

