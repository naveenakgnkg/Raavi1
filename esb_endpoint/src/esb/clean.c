#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bmd_parser.h"

void freebmd(BMD *b)
{
    free(b->bmd_envelope->Destination);
    free(b->bmd_envelope->CreationDateTime);
    free(b->bmd_envelope->MessageID);
    free(b->bmd_envelope->MessageType);
    free(b->bmd_envelope->Sender);
    free(b->bmd_envelope->Signature);
    free(b->bmd_envelope->ReferenceID);
    free(b->bmd_envelope);
    free(b->bmd_payload);
}