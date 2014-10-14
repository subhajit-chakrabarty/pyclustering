from PIL import Image;

from support import draw_image_segments, read_image;

from samples.definitions import IMAGE_SIMPLE_SAMPLES, IMAGE_MAP_SAMPLES;

from clustering.kmeans import kmeans;


def template_segmentation_image(source, start_centers):    
    data = read_image(source);

    clusters = kmeans(data, start_centers);
    draw_image_segments(source, clusters);
    
    
def segmentation_image_simple1():
    template_segmentation_image(IMAGE_SIMPLE_SAMPLES.IMAGE_SIMPLE01, [[255, 0, 0], [0, 0, 255], [180, 136, 0], [255, 255, 255]]);

def segmentation_image_simple2():
    template_segmentation_image(IMAGE_SIMPLE_SAMPLES.IMAGE_SIMPLE02, [[255, 0, 0, 128], [0, 0, 255, 128], [180, 136, 0, 128], [255, 255, 255, 128]]);
    
def segmentation_image_simple3():
    template_segmentation_image(IMAGE_SIMPLE_SAMPLES.IMAGE_SIMPLE03, [[255, 0, 0, 128], [0, 0, 255, 128], [180, 136, 0, 128]]);    
    
def segmentation_image_simple4():
    template_segmentation_image(IMAGE_SIMPLE_SAMPLES.IMAGE_SIMPLE04, [[0, 128, 0, 128], [255, 0, 0, 128]]); 
    
def segmentation_image_beach():   
    template_segmentation_image(IMAGE_SIMPLE_SAMPLES.IMAGE_SIMPLE_BEACH, [[153, 217, 234, 128], [0, 162, 232, 128], [34, 177, 76, 128], [255, 242, 0, 128]]);
    
def segmentation_image_nil():
    template_segmentation_image(IMAGE_MAP_SAMPLES.IMAGE_NILE_SMALL, [[54, 64, 39], [193, 171, 134], [26, 71, 128]]);
    
    
segmentation_image_simple1();
segmentation_image_simple2();
segmentation_image_simple3();
segmentation_image_simple4();
segmentation_image_beach();

segmentation_image_nil();