#pragma once

#include "Quaternion.hpp"

namespace FastMath
{
template<typename T>
struct Transform
{
    explicit constexpr Transform( const Vector<T, 3>&  scale          = Vector<T, 3> { 1, 1, 1 },
                                  const Vector<T, 3>&  translate      = Vector<T, 3> { 0, 0, 0 },
                                  const Vector<T, 3>&  rotationOrigin = Vector<T, 3> { 0, 0, 0 },
                                  const Quaternion<T>& rotation       = Quaternion<T>::IDENTITY ) noexcept;

    const Vector<T, 3>& getScale() const noexcept;

    void setScale( const Vector<T, 3>& scale ) noexcept;

    const Vector<T, 3>& getTranslate() const noexcept;

    void setTranslate( const Vector<T, 3>& translate ) noexcept;

    const Vector<T, 3>& getRotationOrigin() const noexcept;

    void setRotationOrigin( const Vector<T, 3>& rotationOrigin ) noexcept;

    const Quaternion<T>& getRotation() const noexcept;

    void setRotation( const Quaternion<T>& rotation ) noexcept;

    const Matrix<T, 4>& getMatrix() const noexcept;

private:
    void rebuild() const;

    Vector<T, 3>  scale;
    Vector<T, 3>  translate;
    Vector<T, 3>  rotationOrigin;
    Quaternion<T> rotation;

    mutable Matrix<T, 4, 4> matrix;

    // Matrix needs to be rebuilt.
    mutable bool isDirty;
};

template<typename T>
constexpr Transform<T>::Transform( const Vector<T, 3>& scale, const Vector<T, 3>& translate, const Vector<T, 3>& rotationOrigin, const Quaternion<T>& rotation ) noexcept
: scale { scale }
, translate { translate }
, rotationOrigin { rotationOrigin }
, rotation { rotation }
, matrix { Matrix<T, 4>::IDENTITY }
, isDirty { false }
{}

template<typename T>
const Vector<T, 3>& Transform<T>::getScale() const noexcept
{
    return scale;
}

template<typename T>
void Transform<T>::setScale( const Vector<T, 3>& scale ) noexcept
{
    this->scale = scale;
    isDirty     = true;
}

template<typename T>
const Vector<T, 3>& Transform<T>::getTranslate() const noexcept
{
    return translate;
}

template<typename T>
void Transform<T>::setTranslate( const Vector<T, 3>& translate ) noexcept
{
    this->translate = translate;
    isDirty         = true;
}

template<typename T>
const Vector<T, 3>& Transform<T>::getRotationOrigin() const noexcept
{
    return rotationOrigin;
}

template<typename T>
void Transform<T>::setRotationOrigin( const Vector<T, 3>& rotationOrigin ) noexcept
{
    this->rotationOrigin = rotationOrigin;
    isDirty              = true;
}

template<typename T>
const Quaternion<T>& Transform<T>::getRotation() const noexcept
{
    return rotation;
}

template<typename T>
void Transform<T>::setRotation( const Quaternion<T>& rotation ) noexcept
{
    this->rotation = rotation;
    isDirty        = true;
}

template<typename T>
const Matrix<T, 4>& Transform<T>::getMatrix() const noexcept
{
    if ( isDirty )
        rebuild();

    return matrix;
}

template<typename T>
void Transform<T>::rebuild() const
{
    // TODO: Optimize this...
    matrix = FastMath::translate( translate );
    matrix *= FastMath::translate( rotationOrigin );
    matrix *= FastMath::toMat4( rotation );
    matrix *= FastMath::translate( -rotationOrigin );
    matrix *= FastMath::scale( scale );

    isDirty = false;
}

using TransformF = Transform<float>;
using TransformD = Transform<double>;

}  // namespace FastMath
