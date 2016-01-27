/*!
* @File: rbm.hpp
* @Author: kamilrocki
* @Email: kmrocki@us.ibm.com
* @Created:	2015-04-26 10:11:19
* @Last Modified by:   kamilrocki
* @Last Modified time: 2015-10-16 10:10:50
* \brief Contains RBM definition.
*/

#ifndef __CXXRBM_H__
#define __CXXRBM_H__

#include <types/matrix.h>

enum class NTYPE {BINARY, GAUSSIAN, RELU};
enum class LTYPE {CD, PCD};


using namespace mic::types;

namespace mic {

/**
 * \namespace mic::rbm
 * \brief Namespace containing RBM (Restricted Boltzmann Machine) related structures, classes and functions.
 * \author tkornuta
 */
namespace rbm {

/**
 * \brief Class representing Restricted Boltzmann Machine (RBM).
 * \author krocki
 */
class RBM {

  public:

	RBM() = default;

	/*!
	 * Constructor with reduced number of parameters. Sets parameters and allocates matrices.
	 * @param n_visible Number of units in the visible (input) layer.
	 * @param n_hidden Number of units in the hidden layer.
	 * @param b_size Batch size.
	 * @param dm Display mode (to be removed).
	 */
	RBM(size_t n_visible, size_t n_hidden, size_t b_size, DISPLAY_MODE dm);

	/*!
	 * Constructor.
	 * @param n_visible
	 * @param n_hidden
	 * @param v_type
	 * @param h_type
	 * @param l_type
	 * @param dm
	 * @param b_size
	 */
	RBM(size_t n_visible, size_t n_hidden, NTYPE v_type, NTYPE h_type, LTYPE l_type = LTYPE::PCD,
	    DISPLAY_MODE dm = DISPLAY_MODE::DEFAULT_MODE, size_t b_size = 1);

	/*!
	 * Destructor. Deallocates all matrices.
	 */
	virtual ~RBM();

	/*!
	 * ?
	 * @param in
	 */
	void up(Matrix<float>* in);
	/*!
	 * ?
	 * @param in
	 */
	void down(Matrix<float>* in);


	/*!
	 * Computes the statistics. TODO: remove.
	 */
	void compute_statistics();

	/*!
	 * Adaptation.
	 * @param alpha
	 * @param decay
	 * @param sparsecost
	 * @param sparsetarget
	 * @param sparsedamping
	 */
	void adapt(float alpha = 0.001f, float decay = 0.0000f, float sparsecost = 0.0f,
	           float sparsetarget = 0.1f, float sparsedamping = 0.0f);

	/*!
	 * Serializes the RBM settings into ostream.
	 * @param os
	 */
	virtual void serialize(std::ostream& os) const;

	/*!
	 * Number of units in input (visible) layer.
	 */
	size_t num_input;

	/*!
	 * Number of units in hidden (output?) layer.
	 */
	size_t num_output;

	/*!
	 * Batch size - size of data samples (images, letters etc.) trained at once.
	 */
	size_t batch_size;


	Matrix<float>* W;
	Matrix<float>* sigma;
	Matrix<float>* b;
	Matrix<float>* c;

	Matrix<float>* W_delta;
	Matrix<float>* b_delta;
	Matrix<float>* c_delta;

	Matrix<float>* h;
	Matrix<float>* hidmeans;
	Matrix<float>* hidmeans_inc;
	Matrix<float>* hidmeans_inc_rep;
	Matrix<float>* sparsegrads;
	Matrix<float>* H2;
	Matrix<float>* hn;
	Matrix<float>* H;
	Matrix<float>* rv;
	Matrix<float>* rh;

	Matrix<float>* v;
	Matrix<float>* vn;
	Matrix<float>* ve;
	Matrix<float>* pc;

	Matrix<float>* posprods;
	Matrix<float>* negprods;

	float err;
	float hsum;
	float I;
	double mflops;

	NTYPE visible_type;
	NTYPE hidden_type;
	LTYPE learning_type;

};

} /* namespace rbm */
} /* namespace mic */

#endif /*__RBM_H__*/
