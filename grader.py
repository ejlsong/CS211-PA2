#!/usr/bin/env python3
import autograde
import os, os.path

assignment_name = 'PA2'
release='1'

autograde.Test.time_limit = 60

class ParamTests(autograde.FileTests):
    def get_tests(self, project, prog, build_dir, data_dir):
        test_group = project + ':' + self.name if self.name else project

        # gather the names of the reference files
        fnames = [fname for fname in os.listdir(data_dir)
                    if fname.startswith(self.ref_prefix)
                    and fname.endswith(self.suffix)]
        fnames.sort()

        prog = './' + prog

        for ref_name in fnames:
            autograde.logger.debug('Ref_name %r', ref_name)
            parts = ref_name[len(self.ref_prefix):].split('.')
            if len(parts) != 3:
                autograde.logger.warning('Malformed reference file: %r', ref_name)
                continue

            arg = os.path.join(data_dir, f'manifest.{parts[0]}.txt')
            width = parts[1]

            if not os.path.exists(arg):
                autograde.logger.warning('Manifest not found: %r', ref_name)
                continue

            ref = os.path.join(data_dir, ref_name)

            yield self.Test(cmd        = [prog, width, arg],
                            input_file = arg,
                            ref_file   = ref,
                            category   = self.category,
                            group      = test_group,
                            weight     = self.weight,
                            dir        = build_dir)


assignment = ParamTests.Project('knapsack', weight=5)

if __name__ == '__main__':
    autograde.main(assignment_name, assignment, release)
