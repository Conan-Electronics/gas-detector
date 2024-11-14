from PIL import Image


def convert_16text(filename):
    im = Image.open(filename).convert('L')
    result = [[], []]
    for line in range(2):
        for col in range(im.width):
            data = 0
            for row in range(8):
                if im.getpixel((col, line * 8 + row)) > 128:
                    data |= 1 << row
            result[line].append(data)
    print("{", ", ".join("0x{:02X}".format(a) for a in result[0]), "},")
    print("{", ", ".join("0x{:02X}".format(a) for a in result[1]), "}")
    print(len(result[0]))


def convert_digits():
    im = Image.open("digits.png").convert('L')
    for digit in range(10):
        res = []
        for col in range(6):
            data = 0
            for row in range(8):
                if im.getpixel((col + digit * 6, row)) > 128:
                    data |= 1 << row
            res.append(data)
        print("{", ", ".join("0x{:02X}".format(a) for a in res), "},")


def convert_8text(filename):
    im = Image.open(filename).convert('L')
    result = []
    for col in range(im.width):
        data = 0
        for row in range(8):
            if im.getpixel((col, row)) > 128:
                data |= 1 << row
        result.append(data)
    print("{", ", ".join("0x{:02X}".format(a) for a in result), "},")
    print(len(result))


# convert_16text("cal_text.png")
# convert_digits()
convert_8text("warn_text.png")
