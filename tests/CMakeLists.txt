if(BUILD_TESTING)
    add_executable(tests
        app_app_controller.cpp
        app_commands.cpp
        board_board.cpp
        board_rank.cpp
        board_square.cpp
        command_command.cpp
        game_castling_ability.cpp
        game_game_players.cpp
        game_move.cpp
        game_pieces.cpp
        game_player.cpp
        game_win_conditions.cpp
        grid_coords.cpp
        grid_grid.cpp
        grid_gridcell.cpp
        input_eval_input.cpp
        move_generator_list_moves.cpp
        move_generator_moves.cpp
        notation_fen.cpp
        output_player_side.cpp
        output_print_board.cpp
        output_print_game_over.cpp
        output_print_move.cpp
        output_print_piece.cpp
        output_print_square.cpp
    )

    set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(tests PUBLIC cxx_std_20)
    target_compile_options(tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_link_options(tests PRIVATE ${SANITIZER_LINK_OPTIONS})
    target_link_libraries(tests PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_chess Catch2::Catch2WithMain)

    add_test(NAME tests COMMAND tests)
endif()
