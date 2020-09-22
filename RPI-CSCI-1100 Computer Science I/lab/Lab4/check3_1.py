from PIL import Image ##must import Image first to be able to use it
import check2_helper
import panoramio as pan

address = input("Enter an address ==> ")
urls = pan.getPhotos(address,4)

if len(urls)>=4:
    final_im = Image.new("RGB", (512,512), "white") # use mode 'RGB', color 'white'
    im_1 = pan.openphoto(urls[0])
    im_2 = pan.openphoto(urls[1])
    im_3 = pan.openphoto(urls[2])
    im_4 = pan.openphoto(urls[3])

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
else:
    print("Not enough images found")