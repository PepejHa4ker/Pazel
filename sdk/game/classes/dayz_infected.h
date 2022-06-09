//
// Created by pepej on 09.06.2022.
//

#ifndef PAZEL_DAYZ_INFECTED_H
#define PAZEL_DAYZ_INFECTED_H

#include "entity.h"
#include "enfusion.h"

class infected : public entity
{
private:
    struct matrix4x4
    {
        float m[12];
    };
public:
    vector get_bone_pos( int index )
    {
        vector out( 0, 0, 0 );
        if( !g_utils.valid_ptr( this ) )
            return out;

        typedef void* ( __thiscall* fn_get_bone_pos )( entity* entity, vector* out, unsigned int index );
        static const fn_get_bone_pos get_bone_pos = reinterpret_cast < fn_get_bone_pos >( get_bone_pos_infected_sig );

        get_bone_pos( this, &out, index );
        return out;
    }

    uint64_t getSkeleton() {
        return *reinterpret_cast<uint64_t*>(this + 0x5D0);
    }

    BOOLEAN getBonePos(uint64_t pSkeleton, visual_state* pVisual, unsigned int index, vector* out) {

        uint64_t animClass = *reinterpret_cast<uint64_t*>(pSkeleton + 0xA0);
        uint64_t matrixClass = *reinterpret_cast<uint64_t*>(animClass + 0xBF0);

        matrix4x4 matrix_a = *reinterpret_cast<matrix4x4*>(pVisual + 0x8);

        auto matrix_b = *reinterpret_cast<vector*>(matrixClass + 0x54 + index * sizeof(matrix4x4));

        out->x = (matrix_a.m[0] * matrix_b.x) + (matrix_a.m[3] * matrix_b.y) + (matrix_a.m[6] * matrix_b.z) + matrix_a.m[9];
        out->y = (matrix_a.m[1] * matrix_b.x) + (matrix_a.m[4] * matrix_b.y) + (matrix_a.m[7] * matrix_b.z) + matrix_a.m[10];
        out->z = (matrix_a.m[2] * matrix_b.x) + (matrix_a.m[5] * matrix_b.y) + (matrix_a.m[8] * matrix_b.z) + matrix_a.m[11];

        return TRUE;
    }
};

#endif //PAZEL_DAYZ_INFECTED_H
