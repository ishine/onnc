#include "TGLRN.h"
#include "BM168xCodeEmitter.h"
#include <bmkernel_api.h>

using namespace onnc;

TGLRN::TGLRN(const ::onnx::Node &pNode)
    : Operator(pNode, "LRN"), m_inputAddr(0), m_outputAddr(0), m_k(1)
{

  auto inputs = pNode.inputs();
  auto outputs = pNode.outputs();

  const std::vector< ::onnx::Dimension> inDim = pNode.inputs()[0]->sizes();
  m_N = inDim[0].dim;
  m_C = inDim[1].dim;
  m_H = inDim[2].dim;
  m_W = inDim[3].dim;

  m_alpha = pNode.f(::onnx::Symbol("alpha"));
  m_beta = pNode.f(::onnx::Symbol("beta"));
  if (pNode.hasAttribute(::onnx::Symbol("bias"))) {
    m_k = pNode.f(::onnx::Symbol("bias"));
  }
  m_localSize = pNode.i(::onnx::Symbol("size"));
}

void TGLRN::TGLRN::emit() const
{
  std::cout << "TGLRUN::emit\tm_inputAddr:" << m_inputAddr
            << " m_outputAddr:" << m_outputAddr << " m_N:" << m_N
            << " m_C:" << m_C << " m_H:" << m_H << " m_W:" << m_W
            << " m_alpha:" << m_alpha << "m_localSize:" << m_localSize
            << " m_beta:" << m_beta << "m_k:" << m_k << std::endl;
  bmnet::bmnet_lrn_forward_bmkernel(*bm168x_kernel::getInstance().ctx,
                                    m_inputAddr, m_outputAddr, m_N, m_C, m_H,
                                    m_W, m_alpha, m_localSize, m_beta, m_k);
}