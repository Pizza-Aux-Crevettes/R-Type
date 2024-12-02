export default {
    rules: {
        'type-enum': [2, 'always', ['ADD', 'FIX', 'DOCS', 'STYLE'   , 'REFACTOR', 'TEST', 'RM']],
        'type-case': [2, 'always', 'upper-case'],
        'body-min-length': [2, 'always', 10],
    },
    parserPreset: {
        parserOpts: {
            headerPattern: /^(\w+):\s(.+)$/,
            headerCorrespondence: ['type', 'subject'],
        },
    },
};
