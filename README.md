libSatHelper
==================

Helper library for decoding Satellite Signals.

Features
=========

*   Viterbi27 Decode / Encode (wrapper from [libfec](https://github.com/quiet/libfec))
*   CCSDS ReedSolomon Decode (wrapper from [libfec](https://github.com/quiet/libfec))
*   ReedSolomon [De]Interleaver
*   Correlator for Sync Word
*   Packet Phase Ambiguity Fixer (For 0, 90, 180, 270 degrees and IQ Inversion)

How to build
============

This Library depends on [libfec](https://github.com/quiet/libfec). Please make sure you have it installed before trying to compile SatHelper.

The **libsathelper** can be compiled in three modes: `Debug Shared`, `Release Shared`, `Release Static`. The `static` and `shared` refers to the linking mode of the library (the shared will generate a **.so** file and static will generate a **.a** file). For example GOES LRIT Decoder have Shared and Static builds using **libsathelper**.

For compiling, just enter on one of the folders `Debug`, `Release`, `Release (Static)` and run `make`. You can also use `Eclipse CDT` to compile the project.