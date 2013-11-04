if !exists('g:loaded_twinkle')
    runtime! plugin/twinkle.vim
endif

let s:save_cpo = &cpo
set cpo&vim

let s:p_base = {}

function! twinkle#pconnector#new(host, port, command)
    if type(a:host) != type('')
        throw 'pconnector ERROR: host is NOT string.'
    endif

    if type(a:port) != type(0)
        throw 'pconnector ERROR: port is NOT number.'
    endif

    if type(a:command) != type('')
        throw 'pconnector ERROR: command is NOT number.'
    endif

    let s:p_base.host = a:host
    let s:p_base.port = a:port
    let s:p_base.command = a:command
    let s:p_base.inner_cnt = 0

    return deepcopy(s:p_base)
endfunction


function! s:p_base.start()
    if self.is_run()
        return
    endif

    let self.process = vimproc#popen2(self.command)
endfunction


function! s:p_base.stop()
    if !self.is_run()
        return
    endif

    call self.process.waitpid()
    unlet self.process
endfunction


function! s:p_base.is_run()
    if !exists('self.process')
        return 0
    endif

    " シグナル0で指定したプロセスが存在するかを見る
    " TODO: If an error is occurred, it returns 1 for error and sets |vimproc#get_last_errmsg()|.
    return (vimproc#kill(self.process.pid, 0) == 0)
endfunction


function! s:p_base.send(command)
    try
        let sock = vimproc#socket_open('localhost', self.port)
    catch /.*/
        return
    endtry

    call sock.write(a:command)
    call sock.close()
endfunction


let &cpo = s:save_cpo
unlet s:save_cpo
