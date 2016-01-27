/*!
 * \file IBMFontMatrixImporter.cpp
 * \brief Contains definition of methods of importer responsible for importing/loading characters from IBM VGA font dataset.
 * \author tkornut
 * \date Dec 22, 2015
 */

#include <data_io/IBMFontMatrixImporter.hpp>

#include <data_io/IBMFonts.hpp>

namespace mic {
namespace data_io {

IBMFontMatrixImporter::IBMFontMatrixImporter(std::string node_name_) : Importer (node_name_),
		font_type("font_type",font16x16_type)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(font_type);
}

bool IBMFontMatrixImporter::importData(){

	LOG(LSTATUS) << "Importing IBM VGA fonts of size " << ( font_type == font8x8_type ? "8x8" : "16x16");

	// Select adequate font table.
//	const uint8_t* font_table = ( font_type == font8x8_type ? font8x8_table : font16x16_table );

//	const uint16_t*  mask = ( font_type == font8x8_type ? mask8x8 : mask16x16 );

	// "Load font dataset with labels.
	for(size_t i=1; i < 94; i++ ) {

		// Create new matrix of size font_type x font_type (8x8 v 16x16).
		mic::types::matrix_float_ptr_t m (new mic::types::matrix_float_t(font_type, font_type));

		if (font_type == font8x8_type) {
			// Generate 8x8 characters - font_type = 8.

			for (size_t r = 0; r < 8; r++) {
				// Get line.
				uint8_t line = font8x8_table[8*i+r];
				// Iterate through characters in given line.
				for (size_t c = 0; c < 8; c++) {
					(*m)(r, c) = ((line & mask8x8[8-c]) != 0);
				}//: for
			}//: for
		} else {
			// Generate 16x16 characters - font_type = 16.

			for (size_t r = 0; r < 16; r++) {
		        uint16_t line = ((uint16_t*)font16x16_table)[16 *i+r];
		        for (size_t c = 0; c < 16; c++) {
		            (*m)(r, c) = ((line & mask16x16[c]) != 0);
		        }//: for
		    }//: for

	    }//: else

		// Add character and label to vectors.
		data.push_back(m);
		labels.push_back(std::make_shared <char> (font_labels_table[i]) );

	}//: for
	LOG(LINFO) << "Imported " << data.size() << " fonts";
	return true;
}


} /* namespace data_io */
} /* namespace mic */
