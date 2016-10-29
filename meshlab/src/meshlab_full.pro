#config += debug_and_release
TEMPLATE      = subdirs
CONFIG += ordered
SUBDIRS       = common \
                meshlab \
                meshlabserver \
# IO plugins
                meshlabplugins/io_base\
                meshlabplugins/io_bre\
                meshlabplugins/io_collada \
				meshlabplugins/io_ctm \
                meshlabplugins/io_json \
                meshlabplugins/io_u3d\
                meshlabplugins/io_tri\
                meshlabplugins/io_x3d \
                meshlabplugins/io_gts \
                meshlabplugins/io_expe \
                meshlabplugins/io_pdb \
				meshlabplugins/filter_aging \
				meshlabplugins/filter_ao \
                meshlabplugins/filter_autoalign \
                meshlabplugins/filter_camera \
                meshlabplugins/filter_bnpts \
                meshlabplugins/filter_clean \
                meshlabplugins/filter_colorize \
                meshlabplugins/filter_colorproc \
				meshlabplugins/filter_color_projection \
                meshlabplugins/filter_create \
				meshlabplugins/filter_dirt \
                meshlabplugins/filter_fractal \
                meshlabplugins/filter_func \
                meshlabplugins/filter_img_patch_param \
				meshlabplugins/filter_isoparametrization \
                meshlabplugins/filter_layer \
                meshlabplugins/filter_measure \
                meshlabplugins/filter_meshing \
				meshlabplugins/filter_mutualinfoxml \
                meshlabplugins/filter_mls \
                meshlabplugins/filter_photosynth \
                meshlabplugins/filter_poisson \
                meshlabplugins/filter_qhull \
				meshlabplugins/filter_quality \
                meshlabplugins/filter_sampling \
				meshlabplugins/filter_sdfgpu \
                meshlabplugins/filter_select \
                meshlabplugins/filter_ssynth \
                meshlabplugins/filter_texture \
                meshlabplugins/filter_trioptimize \
                meshlabplugins/filter_unsharp \
                meshlabplugins/filter_zippering \
				# rendering stuff
                meshlabplugins/render_splatting \
                meshlabplugins/render_gdp \
                meshlabplugins/render_radiance_scaling \
                meshlabplugins/render_rfx \
                meshlabplugins/edit_select \
                meshlabplugins/edit_pickpoints \
                meshlabplugins/edit_measure \
                meshlabplugins/edit_hole \
                meshlabplugins/edit_paint\
				meshlabplugins/edit_point\
                meshlabplugins/edit_quality \
                meshlabplugins/edit_texture \
				meshlabplugins/edit_manipulators \
                meshlabplugins/edit_arc3D \
                sampleplugins/sampleedit \
                sampleplugins/samplefilter \
                sampleplugins/samplefilterdyn \
              sampleplugins/io_m\
               sampleplugins/filter_geodesic \
               sampleplugins/filter_createiso
