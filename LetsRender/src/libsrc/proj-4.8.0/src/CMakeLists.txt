set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -fPIC -Wfatal-errors -lm -fpermissive" )

include_directories(.)

set(SRC
  aasincos.c
  adjlon.c
  bch2bps.c
  bchgen.c
  biveval.c
  dmstor.c
  emess.c
  gen_cheb.c
  geocent.c
  geod_for.c
  geod_inv.c
  geod_set.c
  jniproj.c
  mk_cheby.c
  nad_cvt.c
  nad_init.c
  nad_intr.c
  PJ_aea.c
  PJ_aeqd.c
  PJ_airy.c
  PJ_aitoff.c
  pj_apply_gridshift.c
  pj_apply_vgridshift.c
  PJ_august.c
  pj_auth.c
  PJ_bacon.c
  PJ_bipc.c
  PJ_boggs.c
  PJ_bonne.c
  PJ_cass.c
  PJ_cc.c
  PJ_cea.c
  PJ_chamb.c
  PJ_collg.c
  PJ_crast.c
  pj_ctx.c
  pj_datums.c
  pj_datum_set.c
  PJ_denoy.c
  pj_deriv.c
  PJ_eck1.c
  PJ_eck2.c
  PJ_eck3.c
  PJ_eck4.c
  PJ_eck5.c
  pj_ellps.c
  pj_ell_set.c
  PJ_eqc.c
  PJ_eqdc.c
  pj_errno.c
  pj_factors.c
  PJ_fahey.c
  PJ_fouc_s.c
  pj_fwd.c
  PJ_gall.c
  pj_gauss.c
  pj_geocent.c
  PJ_geos.c
  PJ_gins8.c
  PJ_gnom.c
  PJ_gn_sinu.c
  PJ_goode.c
  pj_gridinfo.c
  pj_gridlist.c
  PJ_gstmerc.c
  PJ_hammer.c
  PJ_hatano.c
  PJ_healpix.c
  PJ_igh.c
  PJ_imw_p.c
  pj_init.c
  pj_initcache.c
  pj_inv.c
  PJ_isea.c
  PJ_krovak.c
  PJ_labrd.c
  PJ_laea.c
  PJ_lagrng.c
  PJ_larr.c
  PJ_lask.c
  pj_latlong.c
  PJ_lcca.c
  PJ_lcc.c
  pj_list.c
  pj_log.c
  PJ_loxim.c
  PJ_lsat.c
  pj_malloc.c
  PJ_mbtfpp.c
  PJ_mbtfpq.c
  PJ_mbt_fps.c
  PJ_merc.c
  PJ_mill.c
  pj_mlfn.c
  PJ_mod_ster.c
  PJ_moll.c
  pj_msfn.c
  pj_mutex.c
  PJ_natearth.c
  PJ_nell.c
  PJ_nell_h.c
  PJ_nocol.c
  PJ_nsper.c
  PJ_nzmg.c
  PJ_ob_tran.c
  PJ_ocea.c
  PJ_oea.c
  PJ_omerc.c
  pj_open_lib.c
  PJ_ortho.c
  pj_param.c
  pj_phi2.c
  PJ_poly.c
  pj_pr_list.c
  PJ_putp2.c
  PJ_putp3.c
  PJ_putp4p.c
  PJ_putp5.c
  PJ_putp6.c
  pj_qsfn.c
  pj_release.c
  PJ_robin.c
  PJ_rpoly.c
  PJ_sconics.c
  PJ_somerc.c
  PJ_sterea.c
  PJ_stere.c
  pj_strerrno.c
  PJ_sts.c
  PJ_tcc.c
  PJ_tcea.c
  PJ_tmerc.c
  PJ_tpeqd.c
  pj_transform.c
  pj_tsfn.c
  pj_units.c
  PJ_urm5.c
  PJ_urmfps.c
  pj_utils.c
  PJ_vandg2.c
  PJ_vandg4.c
  PJ_vandg.c
  PJ_wag2.c
  PJ_wag3.c
  PJ_wag7.c
  PJ_wink1.c
  PJ_wink2.c
  pj_zpoly1.c
  proj_etmerc.c
  proj_mdist.c
  proj_rouss.c
  p_series.c
  rtodms.c
  vector1.c)

set_source_files_properties(${SRC} PROPERTIES LANGUAGE CXX)

# Enables c++11.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(--std=c++11 SUPPORTS_STD_CXX11)
    check_cxx_compiler_flag(--std=c++0x SUPPORTS_STD_CXX01)
    if(SUPPORTS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++11")
    elseif(SUPPORTS_STD_CXX01)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++0x")
    else()
        message(ERROR "Compiler does not support --std=c++11 or --std=c++0x.")
    endif()
endif()

add_library(proj ${SRC})

target_link_libraries(proj log)
