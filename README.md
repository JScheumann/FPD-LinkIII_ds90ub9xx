# FPD-LinkIII_ds90ub9xx

It a Kernel Module that work with the ds90ub954 (54) Deserializer and the ds90ub971 (71) Serializer.
To get this to work its neccessary to set the 71 with hardware pin to FPD-Link III Mode.

The Voltage for the CSI Lane seems not be correct if the new Serializer (71) works with the old Deserializer (54). Perhaps this is an issue of the development Boards, not sure about that.

The orignal driver i used here and changed comes from here: [https://github.com/InES-HPMM/FPD-LinkIII_ds90ub95x](https://github.com/InES-HPMM/FPD-LinkIII_ds90ub95x)
