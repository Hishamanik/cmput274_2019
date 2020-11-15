#-----------------------------
# Name: Al Hisham Anik
# ID: 1585385
# CMPUT274, Fall 2019
#
# Major Assignment# 1
#-----------------------------

#This modules are imported globally to be used by the functions below
import bitio
import huffman
import pickle


def read_tree(tree_stream):
    '''Read a description of a Huffman tree from the given compressed
    tree stream, and use the pickle module to construct the tree object.
    Then, return the root node of the tree itself.

    Args:
      tree_stream: The compressed stream to read the tree from.

    Returns:
      A Huffman tree root constructed according to the given description.
    '''
    unpickled_Huffman_tree = pickle.load(tree_stream)
    return unpickled_Huffman_tree


def decode_byte(tree, bitreader):
    """
    Reads bits from the bit reader and traverses the tree from
    the root to a leaf. Once a leaf is reached, bits are no longer read
    and the value of that leaf is returned.

    Args:
      bitreader: An instance of bitio.BitReader to read the tree from.
      tree: A Huffman tree.

    Returns:
      Next byte of the compressed bit stream.
    """
    #Constructing a Huffman tree using the frequency table
    #The function huffman.make_encoding_table takes tree and produces a dictionary mapping bytes to bit sequences
    dictionary_table = huffman.make_encoding_table(tree)
    bit_sequence = bitreader.readbit()

    if bit_sequence == 0:
    	path = (False, )
    elif bit_sequence == 1:
    	path = (True, )

    while True:
      for (key, value) in dictionary_table.items():
      	if value == path:
      		return key
    #reading bit_sequence until it matches with a bit sequence in the dictionary table
      bit_sequence = bitreader.readbit()
      if bit_sequence == 0:
      	path += (False, )
      elif bit_sequence == 1:
      	path += (True, )


def decompress(compressed, uncompressed):
    '''First, read a Huffman tree from the 'compressed' stream using your
    read_tree function. Then use that tree to decode the rest of the
    stream and write the resulting symbols to the 'uncompressed'
    stream.

    Args:
      compressed: A file stream from which compressed input is read.
      uncompressed: A writable file stream to which the uncompressed
          output is written.
    '''
    #reading Huffman tree from the compressed steam and writing the uncompressed version to the bit_writer
    huffman_tree = read_tree(compressed)
    bit_reader = bitio.BitReader(compressed)
    bit_writer = bitio.BitWriter(uncompressed)
    end_of_file = False

    # the util.decode_bytefunction reads coded bits and decode them
    #try and except method is used to raise an exception
    
    while not end_of_file:
    	try:
    		content = decode_byte(huffman_tree, bit_reader)
    		bit_writer.writebits(content, 8)
    	except EOFError:
    		end_of_file = True

 		
def write_tree(tree, tree_stream):
    '''Write the specified Huffman tree to the given tree_stream
    using pickle.

    Args:
      tree: A Huffman tree.
      tree_stream: The binary file to write the tree to.
    '''
    pickle.dump(tree, tree_stream)


def compress(tree, uncompressed, compressed):
    '''First write the given tree to the stream 'compressed' using the
    write_tree function. Then use the same tree to encode the data
    from the input stream 'uncompressed' and write it to 'compressed'.
    If there are any partially-written bytes remaining at the end,
    write 0 bits to form a complete byte.

    Flush the bitwriter after writing the entire compressed file.

    Args:
      tree: A Huffman tree.
      uncompressed: A file stream from which you can read the input.
      compressed: A file stream that will receive the tree description
          and the coded input data.
    '''

    # util.write_tree function write Huffman trees into files using the pickle module 
 	# in Python to serialize the tree
    write_tree(tree, compressed)
    dictionary_table = huffman.make_encoding_table(tree)
    file = uncompressed.read()

    bit_writer = bitio.BitWriter(compressed)
    for byte in file:
    	bit = dictionary_table[byte]
		# i is 0 or 1 inside bit
    	for i in bit:
    		bit_writer.writebit(i)
    bit_writer.flush()