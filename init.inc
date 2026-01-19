Initialize

; set colors
    lda     #$03
    sta     COLOR0+4
    lda     #$72
    sta     COLOR0+0
    lda     #$33
    sta     COLOR0+1
    lda     #$ef
    sta     COLOR0+2

; set display list
    ldy #100
LoopDl:
    lda dlist,y
    sta DlListPtr,y
    dey
    bne LoopDl
    
    lda     #<DlListPtr            ;Set Display list pointer
    sta     SDLSTL
    lda     #>DlListPtr
    sta     SDLSTH
    
; enable DMI
    lda     #$22            ;Enable DMA
    sta     SDMCTL

; Set buffer 1
    jsr SetBuffer1

    rts

