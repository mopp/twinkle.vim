if exists('g:loaded_twinkle')
    finish
endif
let g:loaded_twinkle = 1


let s:save_cpo = &cpo
set cpo&vim


augroup twinkle
    autocmd!
    autocmd VimEnter * call twinkle#start()
    autocmd CursorMoved,CursorMovedI * call twinkle#send(getpos('.')[1])
    autocmd VimLeavePre * call twinkle#stop()
augroup END


let &cpo = s:save_cpo
unlet s:save_cpo
