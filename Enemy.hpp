
#include "Space_object.hpp"
#include "Bullet.hpp"


class Enemy : public Space_object {
private:
    Bullet  *_bullet;
    bool    _active;
    void    _putAllBulletsOnWindow(WINDOW *window);

public:
    Enemy();
    ~Enemy();
    Enemy(Enemy const & obj);

    Enemy &operator=(Enemy const &obj);

    void    recreate();
    void    putEnemyAndBullets(WINDOW *window);
    void    move(WINDOW *window);
    bool    isActive();
    void    deactivate(WINDOW *window);

    int     getEnemyX( void );
    int     getEnemyY( void );
    Bullet  *getBullet();
    void    setActiveFalse( void );

};