#include <WorldTransform.h>
#include "MyMath.h"

 void WorldTransform::UpdateMatrix() {

	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MyMath::Vector3MakeAffineMatrix(scale_, rotation_, translation_);

	// 親があればワールド行列を掛ける
	if (parent_) {
		matWorld_ = MyMath::Multiply(matWorld_, parent_->matWorld_);
	}

	TransferMatrix();

}