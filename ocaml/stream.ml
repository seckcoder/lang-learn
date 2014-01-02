let line_stream_of_channel channel =
    Stream.from (fun _ ->
        try Some (input_line channel) with End_of_file -> None);;

let in_channel = open_in "test.ml";;
let lines = line_stream_of_channel in_channel
