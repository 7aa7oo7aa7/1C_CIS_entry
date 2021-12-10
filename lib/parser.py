import png
import numpy as np
import os

def read_graph_from_png(path):
    # reads png from path,
    # returns 2-dim np.array of pixels
    reader = png.Reader(filename=path)
    png_data = reader.read()
    png_generator = (np.array(i) for i in png_data[2])
    png_data = np.array([row for row in png_generator])
    png_data = png_data / 255
    return png_data

def save_to_file(png_data):
    with open("./png_data", "w+") as f:
        for row in png_data:
            for pixel in row:
                f.write(str(int(pixel)))
            f.write('\n')

def main():
    print("Enter path to .png file and number of vertices:")
    path = input()
    vertex_num = input()
    png_data = read_graph_from_png(path)
    save_to_file(png_data)
    os.system("./solver.out")

if __name__ == '__main__':
    main()
