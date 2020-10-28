#ifndef DISABLE_LOMSE
#ifdef __clang__
#pragma clang diagnostic push
// Ignore warnings in Lomse code: Implicit conversion loses integer precision
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif

#if defined(__linux__)
#include "../src/platform/lomse_linux.cpp"
#elif defined(_WIN32)
#include "../src/platform/lomse_windows.cpp"
#else
#include "../src/platform/lomse_other.cpp"
#endif

#include "../src/agg/src/agg_arc.cpp"
#include "../src/agg/src/agg_bezier_arc.cpp"
#include "../src/agg/src/agg_curves.cpp"
#include "../src/agg/src/agg_gsv_text.cpp"
#include "../src/agg/src/agg_line_aa_basics.cpp"
#include "../src/agg/src/agg_rounded_rect.cpp"
#include "../src/agg/src/agg_trans_affine.cpp"
#include "../src/agg/src/agg_vcgen_contour.cpp"
#include "../src/agg/src/agg_vcgen_markers_term.cpp"
#include "../src/agg/src/agg_vcgen_stroke.cpp"
#include "../src/document/lomse_command.cpp"
#include "../src/document/lomse_document.cpp"
#include "../src/document/lomse_document_cursor.cpp"
#include "../src/document/lomse_document_iterator.cpp"
#include "../src/document/lomse_id_assigner.cpp"
#include "../src/exporters/lomse_ldp_exporter.cpp"
#include "../src/exporters/lomse_lmd_exporter.cpp"
#include "../src/exporters/lomse_mnx_exporter.cpp"
#include "../src/file_system/lomse_file_system.cpp"
#include "../src/file_system/lomse_image_reader.cpp"
#include "../src/file_system/lomse_zip_stream.cpp"
#include "../src/graphic_model/engravers/lomse_accidentals_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_articulation_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_barline_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_beam_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_chord_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_clef_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_coda_segno_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_dynamics_mark_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_engrouters.cpp"
#include "../src/graphic_model/engravers/lomse_fermata_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_instrument_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_key_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_line_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_lyric_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_metronome_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_note_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_octave_shift_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_ornament_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_rest_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_slur_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_technical_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_text_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_tie_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_time_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_tuplet_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_volta_engraver.cpp"
#include "../src/graphic_model/engravers/lomse_wedge_engraver.cpp"
#include "../src/graphic_model/layouters/lomse_blocks_container_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_document_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_inlines_container_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_right_aligner.cpp"
#include "../src/graphic_model/layouters/lomse_score_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_score_meter.cpp"
#include "../src/graphic_model/layouters/lomse_spacing_algorithm.cpp"
#include "../src/graphic_model/layouters/lomse_spacing_algorithm_gourlay.cpp"
#include "../src/graphic_model/layouters/lomse_staffobjs_cursor.cpp"
#include "../src/graphic_model/layouters/lomse_system_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_table_layouter.cpp"
#include "../src/graphic_model/layouters/lomse_text_splitter.cpp"
#include "../src/graphic_model/layouters/lomse_vertical_profile.cpp"
#include "../src/graphic_model/lomse_box_score_page.cpp"
#include "../src/graphic_model/lomse_box_slice.cpp"
#include "../src/graphic_model/lomse_box_slice_instr.cpp"
#include "../src/graphic_model/lomse_box_system.cpp"
#include "../src/graphic_model/lomse_caret.cpp"
#include "../src/graphic_model/lomse_caret_positioner.cpp"
#include "../src/graphic_model/lomse_engravers_map.cpp"
#include "../src/graphic_model/lomse_glyphs.cpp"
#include "../src/graphic_model/lomse_gm_basic.cpp"
#include "../src/graphic_model/lomse_gm_measures_table.cpp"
#include "../src/graphic_model/lomse_graphical_model.cpp"
#include "../src/graphic_model/lomse_handler.cpp"
#include "../src/graphic_model/lomse_overlays_generator.cpp"
#include "../src/graphic_model/lomse_selections.cpp"
#include "../src/graphic_model/lomse_shape_barline.cpp"
#include "../src/graphic_model/lomse_shape_base.cpp"
#include "../src/graphic_model/lomse_shape_beam.cpp"
#include "../src/graphic_model/lomse_shape_brace_bracket.cpp"
#include "../src/graphic_model/lomse_shape_line.cpp"
#include "../src/graphic_model/lomse_shape_note.cpp"
#include "../src/graphic_model/lomse_shape_octave_shift.cpp"
#include "../src/graphic_model/lomse_shape_staff.cpp"
#include "../src/graphic_model/lomse_shape_text.cpp"
#include "../src/graphic_model/lomse_shape_tie.cpp"
#include "../src/graphic_model/lomse_shape_tuplet.cpp"
#include "../src/graphic_model/lomse_shape_volta_bracket.cpp"
#include "../src/graphic_model/lomse_shape_wedge.cpp"
#include "../src/graphic_model/lomse_shapes.cpp"
#include "../src/graphic_model/lomse_sizers.cpp"
#include "../src/graphic_model/lomse_tempo_line.cpp"
#include "../src/graphic_model/lomse_time_grid.cpp"
#include "../src/graphic_model/lomse_timegrid_table.cpp"
#include "../src/graphic_model/lomse_visual_effect.cpp"
#include "../src/graphic_model/lomse_fragment_mark.cpp"
#include "../src/gui_controls/lomse_button_ctrl.cpp"
#include "../src/gui_controls/lomse_checkbox_ctrl.cpp"
#include "../src/gui_controls/lomse_hyperlink_ctrl.cpp"
#include "../src/gui_controls/lomse_progress_bar_ctrl.cpp"
#include "../src/gui_controls/lomse_score_player_ctrl.cpp"
#include "../src/gui_controls/lomse_static_text_ctrl.cpp"
#include "../src/internal_model/lomse_im_algorithms.cpp"
#include "../src/internal_model/lomse_im_attributes.cpp"
#include "../src/internal_model/lomse_im_factory.cpp"
#include "../src/internal_model/lomse_im_figured_bass.cpp"
#include "../src/internal_model/lomse_im_measures_table.cpp"
#include "../src/internal_model/lomse_im_note.cpp"
#include "../src/internal_model/lomse_internal_model.cpp"
#include "../src/internal_model/lomse_model_builder.cpp"
#include "../src/internal_model/lomse_score_algorithms.cpp"
#include "../src/internal_model/lomse_score_utilities.cpp"
#include "../src/internal_model/lomse_staffobjs_table.cpp"
#include "../src/module/lomse_doorway.cpp"
#include "../src/module/lomse_events.cpp"
#include "../src/module/lomse_events_dispatcher.cpp"
#include "../src/module/lomse_image.cpp"
#include "../src/module/lomse_injectors.cpp"
#include "../src/module/lomse_interval.cpp"
#include "../src/module/lomse_logger.cpp"
#include "../src/module/lomse_pitch.cpp"
#include "../src/module/lomse_time.cpp"
#include "../src/mvc/lomse_graphic_view.cpp"
#include "../src/mvc/lomse_interactor.cpp"
#include "../src/mvc/lomse_presenter.cpp"
#include "../src/mvc/lomse_tasks.cpp"
#include "../src/mvc/lomse_view.cpp"
#include "../src/parser/ldp/lomse_ldp_analyser.cpp"
#include "../src/parser/ldp/lomse_ldp_compiler.cpp"
#include "../src/parser/ldp/lomse_ldp_parser.cpp"
#include "../src/parser/lmd/lomse_lmd_analyser.cpp"
#include "../src/parser/lmd/lomse_lmd_compiler.cpp"
#include "../src/parser/lomse_analyser.cpp"
#include "../src/parser/lomse_autobeamer.cpp"
#include "../src/parser/lomse_autoclef.cpp"
#include "../src/parser/lomse_compiler.cpp"
#include "../src/parser/lomse_ldp_elements.cpp"
#include "../src/parser/lomse_ldp_factory.cpp"
#include "../src/parser/lomse_linker.cpp"
#include "../src/parser/lomse_reader.cpp"
#include "../src/parser/lomse_tokenizer.cpp"
#include "../src/parser/lomse_xml_parser.cpp"
#include "../src/parser/mnx/lomse_mnx_analyser.cpp"
#include "../src/parser/mnx/lomse_mnx_compiler.cpp"
#include "../src/parser/mxl/lomse_mxl_analyser.cpp"
#include "../src/parser/mxl/lomse_mxl_compiler.cpp"
#include "../src/render/lomse_calligrapher.cpp"
#include "../src/render/lomse_font_freetype.cpp"
#include "../src/render/lomse_font_storage.cpp"
#include "../src/render/lomse_renderer.cpp"
#include "../src/render/lomse_screen_drawer.cpp"
#include "../src/score/lomse_score_iterator.cpp"
#include "../src/sound/lomse_midi_table.cpp"
#include "../src/sound/lomse_score_player.cpp"

#include "../packages/pugixml/pugixml.cpp"
#if (LOMSE_ENABLE_COMPRESSION == 1)
	#include "../packages/minizip/ioapi.c"
	#include "../packages/minizip/unzip.c"
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
