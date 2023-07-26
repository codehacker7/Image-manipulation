# ImageMagic: Transform Your World of Pixels!

## Introduction 

Welcome to ImageMagic, a fascinating project that empowers you to delve into the realm of image manipulation using linked lists. 
ImageMagic lets you break down an image into distinct parts, store them in a unique linked list (Chain), and perform a series of enchanting operations on each image block. 
With ImageMagic, you can unleash your creativity and explore the captivating possibilities of digital art!

## FeaturesBlock 

Enchantment (block.h): The Block class allows you to wield the power of magic to create enchanting blocks of pixels from an image. You can position the blocks at specific locations on the image canvas and perform incredible transformations like rendering, flipping horizontally, and rotating 90 degrees counter-clockwise.

Chain of Wonders (chain.h): The Chain class is a marvel of linked list artistry, orchestrating a captivating chain of Blocks. Each node in the chain holds a mesmerizing Block, and ImageMagic enables you to perform a series of magical operations on the entire chain, like reversing the sequence, flipping the chain horizontally, and rotating it 90 degrees counter-clockwise.

Image Unleashed (chain.h): With ImageMagic, you have the power to unleash the charm of your magical chain onto a canvas. The Render function in the Chain class allows you to conjure a masterpiece by rendering the chain of blocks into a single output image, with the choice to specify the number of columns.

## Getting Started

To unlock the realm of ImageMagic, follow these steps:

Immerse yourself in the world of C++ enchantments.
Embrace the magic of creativity and image manipulation.
Brew your potion by cloning or downloading the repository.
Unveil the secrets of the project by exploring it in your favorite C++ development environment.
Cast the incantation to build the project and unleash the executable.
Embark on a magical journey as you run the executable and follow the guide to provide an input image and dimensions for the enchanting blocks.

## Usage
UsageEnchanting Blocks: Unleash your creativity with the Block class by creating captivating blocks, experimenting with magical transformations (e.g., flip horizontally, rotate counter-clockwise), and rendering them onto the canvas of an output image.

Chain of Wonders: The Chain class invites you to conjure an enchanting chain of blocks, perform mystical operations (e.g., reversing, flipping horizontally, rotating counter-clockwise), and orchestrate an extraordinary masterpiece.

Unveil the Magic: When you are ready to reveal the full magic of your chain, use the Render function in the Chain class to bring your creation to life. Watch in awe as your chain of blocks merges into a magnificent output image, with the choice to specify the number of columns.

# Examples
// Example usage of Block and Chain classes
#include "block.h"
#include "chain.h"

int main() {
  // Load an input image
  PNG inputImage;
  inputImage.readFromFile("input.png");

  // Define the block size
  unsigned int blockSize = 10;

  // Create a chain of blocks from the input image
  Chain imageChain(inputImage, blockSize);

  // Flip the chain horizontally
  imageChain.FlipHorizontal(inputImage.width());

  // Rotate the chain counter-clockwise
  imageChain.RotateCCW(inputImage.width());

  // Render the chain into a single output image with 5 columns
  PNG outputImage = imageChain.Render(5);

  // Save the output image
  outputImage.writeToFile("output.png");

  return 0;
}

## Contributing
Contributions to this project are welcome! 
If you find any bugs, have improvements or feature suggestions, feel free to open an issue or submit a pull request.

# License
ImageMagic is licensed under the mythical MIT License. 
To unlock the full potential of this enchanting realm, refer to the LICENSE file for magical details.

# Acknowledgments
The inspiration for ImageMagic comes from the wonders of digital art and image manipulation. 
Special thanks to the community of developers, who, like modern-day wizards, have shared their wisdom to create the magical world of C++ and linked lists. 
May the pixels be ever in your favor!
