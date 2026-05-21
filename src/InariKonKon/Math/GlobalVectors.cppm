export module GlobalVectors;

import Vector;

export namespace ikk::Global::World
{
    inline constexpr Vec3f Right    =  Vec3f::X();
    inline constexpr Vec3f Up       =  Vec3f::Y();
    inline constexpr Vec3f Forward  = -Vec3f::Z();
}