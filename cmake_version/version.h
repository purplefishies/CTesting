
// These variables are autogenerated and compiled
// into the library by the version.cmake script
extern "C"
{
    extern const char* GIT_TAG;
    extern const char* GIT_REV;
    extern const char* GIT_BRANCH;
}

const char* libfive_git_version(void)
{
    return GIT_TAG;
}

const char* libfive_git_revision(void)
{
    return GIT_REV;
}

const char* libfive_git_branch(void)
{
    return GIT_BRANCH;
}
