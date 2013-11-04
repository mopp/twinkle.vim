if !exists('g:loaded_twinkle')
    runtime! plugin/twinkle.vim
endif

let s:save_cpo = &cpo
set cpo&vim

function! twinkle#start()
    let s:connection = twinkle#pconnector#new('localhost', 14474, "ruby " . g:twinkle_ruby_file_path . " 14474")
    call s:connection.start()
endfunction


function! twinkle#send(num)
    let str = string(a:num)

    while strlen(str) < 6
        let str = '0' . str
    endwhile

    call s:connection.send(str)
endfunction


function! twinkle#stop()
    call s:connection.stop()
endfunction



let &cpo = s:save_cpo
unlet s:save_cpo
