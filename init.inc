Initialize

; set colors
    lda     #$00
    sta     COLOR0+4
    lda     #$72
    sta     COLOR0+0
    lda     #$33
    sta     COLOR0+1
    lda     #$ec
    sta     COLOR0+2

; set display list
    lda     #<dlist            ;Set Display list pointer
    sta     SDLSTL
    lda     #>dlist
    sta     SDLSTH
    
; enable DMI
    lda     #$22            ;Enable DMA
    sta     SDMCTL
    

    rts
    
; ==========================================
;Display list data
; ==========================================
dlist
    .byte $70,$70,$70
    .byte $4d,#<Buffer1, #>Buffer1
    REPEAT 95
    .byte $0d
    REPEND
    .byte $41,$00,$10
dlistend equ .



