// Copyright (c) Facebook, Inc. and its affiliates. All rights reserved.

#pragma once
#include <torch/extension.h>
#include <tuple>

// Compute areas of mesh faces using packed representation.
//
// Inputs:
//    verts: FloatTensor of shape (V, 3) giving vertex positions.
//    faces: LongTensor of shape (F, 3) giving faces.
//
// Returns:
//    areas: FloatTensor of shape (F,) where areas[f] is the area of faces[f].
//    normals: FloatTensor of shape (F, 3) where normals[f] is the normal of
//    faces[f]
//

// Cuda implementation.
std::tuple<at::Tensor, at::Tensor> face_areas_cuda(
    at::Tensor verts,
    at::Tensor faces);

// Implementation which is exposed.
std::tuple<at::Tensor, at::Tensor> face_areas_normals(
    at::Tensor verts,
    at::Tensor faces) {
  if (verts.type().is_cuda() && faces.type().is_cuda()) {
#ifdef WITH_CUDA
    return face_areas_cuda(verts, faces);
#else
    AT_ERROR("Not compiled with GPU support.");
#endif
  }
  AT_ERROR("Not implemented on the CPU.");
}
