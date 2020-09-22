from PIL import Image ##must import Image first to be able to use it
import check2_helper

final_im = Image.new("RGB", (512,512), "white") # use mode 'RGB', color 'white'
im_1 = Image.open("ca.jpg")
im_2 = Image.open("im.jpg")
im_3 = Image.open("hk.jpg")
im_4 = Image.open("bw.jpg")

im_1 = check2_helper.make_square(im_1)
im_2 = check2_helper.make_square(im_2)
im_3 = check2_helper.make_square(im_3)
im_4 = check2_helper.make_square(im_4)

im_1 = im_1.resize((256,256))
im_2 = im_2.resize((256,256))
im_3 = im_3.resize((256,256))
im_4 = im_4.resize((256,256))

final_im.paste(im_1,(0,0))
final_im.paste(im_2,(256,0))
final_im.paste(im_3,(0,256))
final_im.paste(im_4,(256,256))

final_im.show()