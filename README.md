uts-simple
==========

A minimal sequential version of the UTS benchmark designed to be handed out to students.

Compile with

$CC -DBRG_RNG  -o uts uts_shm.cpp rng/brg_sha1.cpp uts.cpp
