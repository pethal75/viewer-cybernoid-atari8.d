    processor 6502    
    
    org     $8000           ;Start of left cartridge area

    include "atari.inc"
    
    include "global.inc"
    include "draw.inc"
    include "init.inc"
    

; ==========================================
; Program start
; ==========================================
Start:
    jsr Initialize
    
    ; test buffer 1
    lda #$11
    sta Buffer1
    sta Buffer1 + 1
    sta Buffer1 + 5
    
    ; enable DMI
    lda     #$22            ;Enable DMA
    sta     SDMCTL
    
    lda #$ff
    sta COLOR_V
    lda #30         ; X = 50
    sta RECT_X
    lda #10         ; Y = 30
    sta RECT_Y

    lda #<Buffer1
    sta ActualBufferAddr
    lda #>Buffer1
    sta ActualBufferAddr + 1
    
    ; infinite loop
Begin

    ; Wait for screen
    lda RTCLOK2
WaitVBL
    cmp RTCLOK2
    beq WaitVBL
    
    lda #$00
    sta COLOR_V
    jsr DrawRect    ; Call routine
    
    ; Increase X,Y coordinates
    inc RECT_X
    inc RECT_X
    inc RECT_Y
    inc RECT_Y
    ; Check X,Y coordinates out of screen
    lda RECT_X
    cmp #144
    bcc CheckY      ; If X < 128, skip reset
    lda #0
    sta RECT_X

CheckY
    lda RECT_Y
    cmp #80
    bcc DrawContinue     ; If Y < 64, skip reset
    lda #0
    sta RECT_Y

DrawContinue
    lda #$55
    sta COLOR_V
    jsr DrawRect    ; Call routine
    jsr DrawRect    ; Call routine
 
End
    nop
    jmp     Begin

; ==========================================
;Graphics data
; ==========================================
    align $100   ; ANTIC can only count to $FFF
ImgData1:
ImgData2 equ ImgData1+40*96
    incbin "cybernoid-atari8.d.bin"


; ==========================================
;Cartridge footer
; ==========================================
    org     CARTCS
    .word 	Start	; cold start address
    .byte	$00	; 0 == cart exists
    .byte	$04	; boot cartridge
    .word	Start	; start

